#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gen/jmpbk.h>
#include <gen/bufstm.h>
#include "lvar.h"
#include "fitem.h"

//------------------------------------------------------------------------------
static
void* resize_buffer(void *buf, size_t size)
{
    if( size )
    {
        buf = realloc(buf, size);
        assert( buf );
    }
    else
    {
        if( buf ) free(buf);
        buf = NULL;
    }

    return buf;
}
//------------------------------------------------------------------------------
void iso8583_fitem_init(iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
    assert( obj );
    memset(obj, 0, sizeof(*obj));
}
//------------------------------------------------------------------------------
void iso8583_fitem_init_value(iso8583_fitem_t *obj, int id, const void *data, size_t size)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Constructor that
     *        construct object and set initial values.
     *
     * @param obj  Object instance.
     * @param id   The field ID to be set.
     * @param data The data to be set.
     * @param size Size of the input data.
     */
    assert( obj );

    iso8583_fitem_init(obj);
    iso8583_fitem_set_id(obj, id);
    iso8583_fitem_set_data(obj, data, size);
}
//------------------------------------------------------------------------------
void iso8583_fitem_init_clone(iso8583_fitem_t *obj, const iso8583_fitem_t *src)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Constructor that
     *        construct object and clone values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    iso8583_fitem_init(obj);
    iso8583_fitem_clone(obj, src);
}
//------------------------------------------------------------------------------
void iso8583_fitem_init_move(iso8583_fitem_t *obj, iso8583_fitem_t *src)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Constructor that
     *        construct object and move values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    iso8583_fitem_init(obj);
    iso8583_fitem_movefrom(obj, src);
}
//------------------------------------------------------------------------------
void iso8583_fitem_deinit(iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Destructor.
     *
     * @param obj Object instance.
     */
    assert( obj );
    if( obj->buf ) free(obj->buf);
}
//------------------------------------------------------------------------------
void iso8583_fitem_clone(iso8583_fitem_t *obj, const iso8583_fitem_t *src)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Clone values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    obj->id  = src->id;
    obj->buf = resize_buffer(obj->buf, src->size);
    memcpy(obj->buf, src->buf, src->size);
}
//------------------------------------------------------------------------------
void iso8583_fitem_movefrom(iso8583_fitem_t *obj, iso8583_fitem_t *src)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Move values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    iso8583_fitem_deinit(obj);
    *obj = *src;
    iso8583_fitem_init(src);
}
//------------------------------------------------------------------------------
int iso8583_fitem_encode(const iso8583_fitem_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_fitem_t
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
#warning Not finished!
int lvar_encode(void           *buf,
                size_t          bufsz,
                const void     *data,
                size_t          datsz,
                finfo_eletype_t eletype,
                finfo_lenmode_t lvartype,
                size_t          maxsize,
                int             flags);
}
//------------------------------------------------------------------------------
static
const finfo_t* get_finfo(int id)
{
    return ( ISO8583_FITEM_ID_MIN <= id && id <= ISO8583_FITEM_ID_MAX )?
           ( &finfo_list[id] ):( NULL );
}
//------------------------------------------------------------------------------
static
int elecount_to_bytes(finfo_eletype_t eletype, unsigned elecount)
{
    if( !( eletype & ~FINFO_ELE_N ) )
        return ( elecount + 1 ) >> 1;  // Convert BCD counts to byte counts.
    else if( !( eletype & ~FINFO_ELE_B ) )
        return ( elecount + ( 8 - 1 ) ) >> 3;  // Convert bit counts to byte counts.
    else
        return elecount;
}
//------------------------------------------------------------------------------
static
int read_fixlen_data(bufistm_t *stream, uint8_t *buf, finfo_eletype_t eletype, unsigned elecount)
{
    int readsz = elecount_to_bytes(eletype, elecount);
    return bufistm_read(stream, buf, readsz) ? readsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
static
int read_lvar_data(bufistm_t     *stream,
                   uint8_t       *buf,
                   size_t         bufsz,
                   size_t        *fillsz,
                   const finfo_t *finfo,
                   int            flags)
{
    int readsz = lvar_decode(buf,
                             bufsz,
                             fillsz,
                             bufistm_get_readbuf(stream),
                             bufistm_get_restsize(stream),
                             finfo->eletype,
                             finfo->lenmode,
                             finfo->maxsize,
                             flags);
    if( readsz < 0 ) return readsz;

    return bufistm_read_notify(stream, readsz) ? readsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
int iso8583_fitem_decode(iso8583_fitem_t *obj, const void *data, size_t size, int flags, int id)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Decode from raw data.
     *
     * @param obj   Object instance.
     * @param data  The raw data to be read.
     * @param size  Size of the raw data.
     * @param flags Decode options, see ::iso8583_flags_t for more information.
     * @param id    Field ID of the field item to decode data.
     *
     * @retval Positive Size of data (including zero) read from the input data.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
    assert( obj );

    if( !data ) return ISO8583_ERR_INVALID_ARG;

    bufistm_t stream;
    bufistm_init(&stream, data, size);

    static const size_t bufsz = 9999;
    uint8_t *buf = malloc(bufsz);
    assert( buf );

    int res = 0;
    JMPBK_BEGIN
    {
        int    readsz;
        size_t datasz;

        const finfo_t *finfo = get_finfo(id);
        if( !finfo ) JMPBK_THROW(ISO8583_ERR_INVALID_ARG);

        if( finfo->lenmode == FINFO_LEN_FIXED )
        {
            readsz = read_fixlen_data(&stream, buf, finfo->eletype, finfo->maxsize);
            if( readsz < 0 ) JMPBK_THROW(readsz);

            datasz = readsz;
        }
        else
        {
            readsz = read_lvar_data(&stream, buf, bufsz, &datasz, finfo, flags);
            if( readsz < 0 ) JMPBK_THROW(readsz);
        }

        iso8583_fitem_set_id(obj, id);
        iso8583_fitem_set_data(obj, buf, datasz);

        res = bufistm_get_readsize(&stream);
    }
    JMPBK_CATCH_ALL
    {
        res = JMPBK_ERRCODE;
    }
    JMPBK_END

    free(buf);

    return res;
}
//------------------------------------------------------------------------------
void iso8583_fitem_clean(iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Clean all values it contained.
     *
     * @param obj Object instance.
     */
    assert( obj );
    obj->buf = resize_buffer(obj->buf, 0);
}
//------------------------------------------------------------------------------
int iso8583_fitem_get_id(const iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Get field ID.
     *
     * @param obj Object instance.
     * @return The field ID.
     */
    assert( obj );
    return obj->id;
}
//------------------------------------------------------------------------------
void iso8583_fitem_set_id(iso8583_fitem_t *obj, int id)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Set field ID.
     *
     * @param obj Object instance.
     * @param id  The field ID to be set.
     */
    assert( obj );
    obj->id = id;
}
//------------------------------------------------------------------------------
const void* iso8583_fitem_get_data(const iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Get field data.
     *
     * @param obj Object instance.
     * @return Pointer to the field data; or NULL if no data contained.
     */
    assert( obj );
    return obj->buf;
}
//------------------------------------------------------------------------------
size_t iso8583_fitem_get_size(const iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Get field data size.
     *
     * @param obj Object instance.
     * @return Size of the field data.
     */
    assert( obj );
    return obj->size;
}
//------------------------------------------------------------------------------
void iso8583_fitem_set_data(iso8583_fitem_t *obj, const void *data, size_t size)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Set field data.
     *
     * @param obj  Object instance.
     * @param data The data to be set.
     * @param size Size of the input data.
     */
    assert( obj );

    if( !data ) size = 0;

    obj->buf = resize_buffer(obj->buf, size);
    memcpy(obj->buf, data, size);
}
//------------------------------------------------------------------------------
