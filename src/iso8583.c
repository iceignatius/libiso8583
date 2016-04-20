#include <assert.h>
#include <gen/jmpbk.h>
#include <gen/bufstm.h>
#include "iso8583.h"

//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_init(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
    assert( obj );

    obj->mti = 0;
    iso8583_tpdu_init  (&obj->tpdu);
    iso8583_fields_init(&obj->fields);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_init_clone(iso8583_t *obj, const iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor that
     *        construct object and clone values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    iso8583_init(obj);
    iso8583_clone(obj, src);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_init_move(iso8583_t *obj, iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor that
     *        construct object and move values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    iso8583_init(obj);
    iso8583_movefrom(obj, src);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_deinit(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Destructor.
     *
     * @param obj Object instance.
     */
    assert( obj );
    iso8583_fields_deinit(&obj->fields);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_clone(iso8583_t *obj, const iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Clone values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    obj->tpdu = src->tpdu;
    obj->mti  = src->mti;
    iso8583_fields_clone(&obj->fields, &src->fields);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_movefrom(iso8583_t *obj, iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Move values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    obj->tpdu = src->tpdu;
    obj->mti  = src->mti;
    iso8583_fields_movefrom(&obj->fields, &src->fields);
}
//------------------------------------------------------------------------------
static
int write_tpdu(bufostm_t *stream, const iso8583_tpdu_t *tpdu, int flags)
{
    int fillsz = iso8583_tpdu_encode(tpdu,
                                     bufostm_get_writebuf(stream),
                                     bufostm_get_restsize(stream),
                                     flags);
    if( fillsz < 0 ) return fillsz;

    return bufostm_write_notify(stream, fillsz) ? fillsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
static
int write_mti(bufostm_t *stream, int mti, int flags)
{
    int fillsz = iso8583_mti_encode(mti,
                                    bufostm_get_writebuf(stream),
                                    bufostm_get_restsize(stream),
                                    flags);
    if( fillsz < 0 ) return fillsz;

    return bufostm_write_notify(stream, fillsz) ? fillsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
static
int write_fields(bufostm_t *stream, const iso8583_fields_t *fields, int flags)
{
    int fillsz = iso8583_fields_encode(fields,
                                       bufostm_get_writebuf(stream),
                                       bufostm_get_restsize(stream),
                                       flags);
    if( fillsz < 0 ) return fillsz;

    return bufostm_write_notify(stream, fillsz) ? fillsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_encode(const iso8583_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_t
     * @brief Encode to raw data.
     *
     * @param obj   Object instance.
     * @param buf   The output buffer.
     * @param size  Size of the output buffer.
     * @param flags Encode options, see ::iso8583_flags_t for more information.
     *
     * @retval Positive Size of data (including zero) filled to the output buffer.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
    assert( obj );

    if( !buf ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    bufostm_t stream;
    bufostm_init(&stream, buf, size);

    int res = 0;
    JMPBK_BEGIN
    {
        int      fillsz;
        uint8_t *sizehdr = NULL;

        if( flags & ISO8583_FLAG_HAVE_SIZEHDR )
        {
            // Save 2 bytes for size header.
            sizehdr = bufostm_get_writebuf(&stream);
            fillsz  = bufostm_write_notify(&stream, 2);
            if( fillsz < 0 ) JMPBK_THROW(ISO8583_ERR_BUF_NOT_ENOUGH);
        }

        if( flags & ISO8583_FLAG_HAVE_TPDU )
        {
            fillsz = write_tpdu(&stream, &obj->tpdu, flags);
            if( fillsz < 0 ) JMPBK_THROW(fillsz);
        }

        fillsz = write_mti(&stream, obj->mti, flags);
        if( fillsz < 0 ) JMPBK_THROW(fillsz);

        fillsz = write_fields(&stream, &obj->fields, flags);
        if( fillsz < 0 ) JMPBK_THROW(fillsz);

        if( sizehdr )
        {
            size_t totalsize = bufostm_get_datasize(&stream) - 2;
            if( totalsize > 0xFFFF ) JMPBK_THROW(ISO8583_ERR_MSG_TOO_LONG);

            sizehdr[0] = 0xFF & ( totalsize >> 8 );
            sizehdr[1] = 0xFF &   totalsize;
        }

        res = bufostm_get_datasize(&stream);
    }
    JMPBK_CATCH_ALL
    {
        res = JMPBK_ERRCODE;
    }
    JMPBK_END

    return res;
}
//------------------------------------------------------------------------------
static
int read_and_verify_sizehdr(bufistm_t *stream)
{
    uint8_t raw[2];
    if( !bufistm_read(stream, raw, sizeof(raw)) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    size_t value = ( raw[0] << 8 ) | raw[1];

    return value <= bufistm_get_restsize(stream) ?
           sizeof(raw) : ISO8583_ERR_SIZEHDR_FAILED;
}
//------------------------------------------------------------------------------
static
int read_tpdu(bufistm_t *stream, iso8583_tpdu_t *tpdu, int flags)
{
    int readsz = iso8583_tpdu_decode(tpdu,
                                     bufistm_get_readbuf(stream),
                                     bufistm_get_restsize(stream),
                                     flags);
    if( readsz < 0 ) return readsz;

    return bufistm_read_notify(stream, readsz) ? readsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
static
int read_mti(bufistm_t *stream, int *mti, int flags)
{
    int readsz = iso8583_mti_decode(mti,
                                    bufistm_get_readbuf(stream),
                                    bufistm_get_restsize(stream),
                                    flags);
    if( readsz < 0 ) return readsz;

    return bufistm_read_notify(stream, readsz) ? readsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
static
int read_fields(bufistm_t *stream, iso8583_fields_t *fields, int flags)
{
    int readsz = iso8583_fields_decode(fields,
                                       bufistm_get_readbuf(stream),
                                       bufistm_get_restsize(stream),
                                       flags);
    if( readsz < 0 ) return readsz;

    return bufistm_read_notify(stream, readsz) ? readsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_decode(iso8583_t *obj, const void *data, size_t size, int flags)
{
    /**
     * @memberof iso8583_t
     * @brief Decode from raw data.
     *
     * @param obj   Object instance.
     * @param data  The raw data to be read.
     * @param size  Size of the raw data.
     * @param flags Decode options, see ::iso8583_flags_t for more information.
     *
     * @retval Positive Size of data (including zero) read from the input data.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
    assert( obj );

    if( !data ) return ISO8583_ERR_INVALID_ARG;

    bufistm_t stream;
    bufistm_init(&stream, data, size);

    int res = 0;
    JMPBK_BEGIN
    {
        int readsz;

        iso8583_clear(obj);

        if( flags & ISO8583_FLAG_HAVE_SIZEHDR )
        {
            readsz = read_and_verify_sizehdr(&stream);
            if( readsz < 0 ) JMPBK_THROW(readsz);
        }

        if( flags & ISO8583_FLAG_HAVE_TPDU )
        {
            readsz = read_tpdu(&stream, &obj->tpdu, flags);
            if( readsz < 0 ) JMPBK_THROW(readsz);
        }

        readsz = read_mti(&stream, &obj->mti, flags);
        if( readsz < 0 ) JMPBK_THROW(readsz);

        readsz = read_fields(&stream, &obj->fields, flags);
        if( readsz < 0 ) JMPBK_THROW(readsz);

        res = bufistm_get_readsize(&stream);
    }
    JMPBK_CATCH_ALL
    {
        iso8583_clear(obj);
        res = JMPBK_ERRCODE;
    }
    JMPBK_END

    return res;
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_clear(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Clear all variables or set to defaults.
     *
     * @param obj Object instance.
     */
    assert( obj );

    obj->mti = 0;
    iso8583_tpdu_init(&obj->tpdu);
    iso8583_fields_clear(&obj->fields);
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_get_mti(const iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get MTI value.
     *
     * @param obj Object instance.
     * @return MTI value of the object.
     *
     * @remarks See mti.h for more operation about MTI.
     */
    assert( obj );
    return obj->mti;
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_set_mti(iso8583_t *obj, int mti)
{
    /**
     * @memberof iso8583_t
     * @brief Set MTI value.
     *
     * @param obj Object instance.
     * @param mti The MIT value to be set.
     *
     * @remarks See mti.h for more operation about MTI.
     */
    assert( obj );
    obj->mti = 0xFFFF & mti;
}
//------------------------------------------------------------------------------
