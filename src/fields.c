#include <assert.h>
#include <gen/jmpbk.h>
#include <gen/bufstm.h>
#include "bitmap.h"
#include "fields.h"

//------------------------------------------------------------------------------
void iso8583_fields_init(iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
    assert( obj );

    memset(obj, 0, sizeof(*obj));
    for(int id=ISO8583_FITEM_ID_MIN; id<=ISO8583_FITEM_ID_MAX; ++id)
    {
        iso8583_fitem_init(&obj->items[id]);
    }
}
//------------------------------------------------------------------------------
void iso8583_fields_init_clone(iso8583_fields_t *obj, const iso8583_fields_t *src)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Constructor that
     *        construct object and clone values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    iso8583_fields_init(obj);
    iso8583_fields_clone(obj, src);
}
//------------------------------------------------------------------------------
void iso8583_fields_init_move(iso8583_fields_t *obj, iso8583_fields_t *src)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Constructor that
     *        construct object and move values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    iso8583_fields_init(obj);
    iso8583_fields_movefrom(obj, src);
}
//------------------------------------------------------------------------------
void iso8583_fields_deinit(iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Destructor.
     *
     * @param obj Object instance.
     */
    assert( obj );

    for(int id=ISO8583_FITEM_ID_MIN; id<=ISO8583_FITEM_ID_MAX; ++id)
    {
        iso8583_fitem_deinit(&obj->items[id]);
    }
}
//------------------------------------------------------------------------------
void iso8583_fields_clone(iso8583_fields_t *obj, const iso8583_fields_t *src)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Clone values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be cloned.
     */
    assert( obj && src );

    obj->count = src->count;
    for(int id=ISO8583_FITEM_ID_MIN; id<= ISO8583_FITEM_ID_MAX; ++id)
    {
        iso8583_fitem_clone(&obj->items[id], &src->items[id]);
    }
}
//------------------------------------------------------------------------------
void iso8583_fields_movefrom(iso8583_fields_t *obj, iso8583_fields_t *src)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Move values from another object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
    assert( obj && src );

    obj->count = src->count;
    for(int id=ISO8583_FITEM_ID_MIN; id<= ISO8583_FITEM_ID_MAX; ++id)
    {
        iso8583_fitem_movefrom(&obj->items[id], &src->items[id]);
    }
}
//------------------------------------------------------------------------------
static
void buildup_bitmap(bitmap_t *bmp, const iso8583_fields_t *fields)
{
    for(const iso8583_fitem_t *item = iso8583_fields_get_first(fields);
        item;
        item = iso8583_fields_get_next(fields, item))
    {
        bitmap_set_id(bmp, item->id);
    }
}
//------------------------------------------------------------------------------
static
int write_bitmap(bufostm_t *stream, const bitmap_t *bmp, int flags)
{
    int fillsz = bitmap_encode(bmp,
                               bufostm_get_writebuf(stream),
                               bufostm_get_restsize(stream),
                               flags);
    if( fillsz < 0 ) return fillsz;

    return bufostm_write_notify(stream, fillsz) ? fillsz : ISO8583_ERR_BUF_NOT_ENOUGH;
}
//------------------------------------------------------------------------------
int iso8583_fields_encode(const iso8583_fields_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_fields_t
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

    if( !buf ) return ISO8583_ERR_INVALID_ARG;

    bufostm_t stream;
    bufostm_init(&stream, buf, size);

    int res = 0;
    JMPBK_BEGIN
    {
        int fillsz;

        bitmap_t bmp;
        bitmap_init(&bmp);
        buildup_bitmap(&bmp, obj);

#warning Not finished!

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
int iso8583_fields_decode(iso8583_fields_t *obj, const void *data, size_t size, int flags)
{
    /**
     * @memberof iso8583_fields_t
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
#warning Not finished!
}
//------------------------------------------------------------------------------
unsigned iso8583_fields_get_count(const iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get count of field items.
     *
     * @param obj Object instance.
     * @return Count of field items.
     */
    assert( obj );
    return obj->count;
}
//------------------------------------------------------------------------------
const iso8583_fitem_t* iso8583_fields_get_item(const iso8583_fields_t *obj, unsigned id)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get field item by field ID.
     *
     * @param obj Object instance.
     * @param id  The specific field ID.
     * @return The field item if succeed; or NULL if no item be found.
     */
    assert( obj );

    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return NULL;

    const iso8583_fitem_t *item = &obj->items[id];
    return item->id ? item : NULL;
}
//------------------------------------------------------------------------------
const iso8583_fitem_t* iso8583_fields_get_first(const iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the first field item.
     *
     * @param obj Object instance.
     * @return The field item if succeed; or NULL if no item be found.
     */
    assert( obj );

    for(int id=ISO8583_FITEM_ID_MIN; id<=ISO8583_FITEM_ID_MAX; ++id)
    {
        const iso8583_fitem_t *item = &obj->items[id];
        if( item->id ) return item;
    }

    return NULL;
}
//------------------------------------------------------------------------------
const iso8583_fitem_t* iso8583_fields_get_next(const iso8583_fields_t *obj, const iso8583_fitem_t *prev)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the next field item.
     *
     * @param obj  Object instance.
     * @param prev The previous field item.
     * @return The field item if succeed; or NULL if no item be found.
     */
    assert( obj );

    if( prev->id < ISO8583_FITEM_ID_MIN ) return NULL;

    for(int id=prev->id+1; id<=ISO8583_FITEM_ID_MAX; ++id)
    {
        const iso8583_fitem_t *item = &obj->items[id];
        if( item->id ) return item;
    }

    return NULL;
}
//------------------------------------------------------------------------------
int iso8583_fields_insert(iso8583_fields_t *obj, const iso8583_fitem_t *item)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Insert item.
     *
     * @param obj  Object instance.
     * @param item The item to be inserted.
     * @return An error code defined in ::iso8583_err_t.
     */
    assert( obj );

    if( !item ) return ISO8583_ERR_INVALID_ARG;

    int id = item->id;
    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return ISO8583_ERR_INVALID_FIELD_ID;

    iso8583_fitem_t *olditem = &obj->items[id];
    if( !olditem->id ) ++ obj->count;

    iso8583_fitem_clone(olditem, item);
    return ISO8583_ERR_SUCCESS;
}
//------------------------------------------------------------------------------
void iso8583_fields_erase(iso8583_fields_t *obj, unsigned id)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Erase field item by field ID.
     *
     * @param obj Object instance.
     * @param id  The specific field ID.
     */
    assert( obj );

    if( !obj->count ) return;
    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return;

    iso8583_fitem_t *item = &obj->items[id];
    if( !item->id ) return;

    iso8583_fitem_clean(item);
    -- obj->count;
}
//------------------------------------------------------------------------------
void iso8583_fields_clean(iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Erase all field items.
     *
     * @param obj Object instance.
     */
    assert( obj );

    obj->count = 0;
    for(int id=ISO8583_FITEM_ID_MIN; id<=ISO8583_FITEM_ID_MAX; ++id)
    {
        iso8583_fitem_clean(&obj->items[id]);
    }
}
//------------------------------------------------------------------------------
