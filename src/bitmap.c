#include <assert.h>
#include <string.h>
#include <gen/bits.h>
#include "bitmap.h"

//------------------------------------------------------------------------------
void bitmap_init(bitmap_t *obj)
{
    assert( obj );
    memset(obj, 0, sizeof(*obj));
}
//------------------------------------------------------------------------------
static
int get_last_id(const bitmap_t *obj)
{
    for(int id=ISO8583_BITMAP_ID_MAX; id; --id)
    {
        if( obj->states[id] )
            return id;
    }

    return 0;
}
//------------------------------------------------------------------------------
int bitmap_encode(const bitmap_t *obj, void *buf, size_t size, int flags)
{
    assert( obj );

    if( !buf ) return ISO8583_ERR_INVALID_ARG;

    bool extend_mode = get_last_id(obj) > 64;
    int  encode_size = extend_mode ? 16 : 8;
    if( size < encode_size ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    memset(buf, 0, encode_size);
    for(int id=ISO8583_BITMAP_ID_MIN; id<=ISO8583_BITMAP_ID_MAX; ++id)
    {
        if( obj->states[id] )
            bits_set_bit(buf, id-1);
    }

    if( extend_mode )
        bits_set_bit(buf, 0);

    return encode_size;
}
//------------------------------------------------------------------------------
int bitmap_decode(bitmap_t *obj, const void *data, size_t size, int flags)
{
    assert( obj );

    if( !data ) return ISO8583_ERR_INVALID_ARG;
    if( !size ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    bool extend_mode = bits_get_bit(data, 0);
    int  decode_size = extend_mode ? 16 : 8;
    if( size < decode_size ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    bitmap_clean(obj);

    int id_max = extend_mode ? ISO8583_BITMAP_ID_MAX : 64;
    for(int id=ISO8583_BITMAP_ID_MIN; id<=id_max; ++id)
    {
        obj->states[id] = bits_get_bit(data, id-1);
    }

    return decode_size;
}
//------------------------------------------------------------------------------
bool bitmap_have_id(const bitmap_t *obj, int id)
{
    assert( obj );

    return id >= ISO8583_BITMAP_ID_MIN &&
           id <= ISO8583_BITMAP_ID_MAX &&
           obj->states[id];
}
//------------------------------------------------------------------------------
int bitmap_get_first_id(const bitmap_t *obj)
{
    for(int id=ISO8583_BITMAP_ID_MIN; id<=ISO8583_BITMAP_ID_MAX; ++id)
    {
        if( obj->states[id] )
            return id;
    }

    return 0;
}
//------------------------------------------------------------------------------
int bitmap_get_next_id(const bitmap_t *obj, int prev_id)
{
    if( prev_id < ISO8583_BITMAP_ID_MIN ) return 0;

    for(int id=prev_id+1; id<=ISO8583_BITMAP_ID_MAX; ++id)
    {
        if( obj->states[id] )
            return id;
    }

    return 0;
}
//------------------------------------------------------------------------------
int bitmap_set_id(bitmap_t *obj, int id)
{
    assert( obj );

    if( id < ISO8583_BITMAP_ID_MIN ||
        id > ISO8583_BITMAP_ID_MAX )
    {
        return ISO8583_ERR_INVALID_ARG;
    }

    obj->states[id] = true;
    return ISO8583_ERR_SUCCESS;
}
//------------------------------------------------------------------------------
void bitmap_clean(bitmap_t *obj)
{
    assert( obj );
    memset(obj, 0, sizeof(*obj));
}
//------------------------------------------------------------------------------
