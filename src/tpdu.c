#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "tpdu.h"

//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_tpdu_init(iso8583_tpdu_t *obj)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
    assert( obj );
    memset(obj, 0, sizeof(*obj));
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_tpdu_encode(const iso8583_tpdu_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_tpdu_t
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

    if( !( flags & ISO8583_FLAG_HAVE_TPDU ) ) return 0;
    if( size < 5 ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    uint8_t *arr = buf;
    arr[0] = 0xFF &   obj->id;
    arr[1] = 0xFF & ( obj->dest >> 8 );
    arr[2] = 0xFF &   obj->dest;
    arr[3] = 0xFF & ( obj->src  >> 8 );
    arr[4] = 0xFF &   obj->src;

    return 5;
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_tpdu_decode(iso8583_tpdu_t *obj, const void *data, size_t size, int flags)
{
    /**
     * @memberof iso8583_tpdu_t
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

    if( !( flags & ISO8583_FLAG_HAVE_TPDU ) ) return 0;
    if( size < 5 ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    const uint8_t *arr = data;
    obj->id   = arr[0];
    obj->dest = ( arr[1] << 8 ) | arr[2];
    obj->src  = ( arr[3] << 8 ) | arr[4];

    return 5;
}
//------------------------------------------------------------------------------
