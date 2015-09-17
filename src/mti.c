#include <stdint.h>
#include "mti.h"

//------------------------------------------------------------------------------
int iso8583_mti_encode(int mti, void *buf, size_t size, int flags)
{
    /**
     * Encode to raw data.
     *
     * @param mti   The MTI value to be operated.
     * @param buf   The output buffer.
     * @param size  Size of the output buffer.
     * @param flags Encode options, see ::iso8583_flags_t for more information.
     *
     * @retval Positive Size of data (including zero) filled to the output buffer.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
    if( !buf ) return ISO8583_ERR_INVALID_ARG;
    if( size < 2 ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    uint8_t *arr = buf;
    arr[0] = 0xFF & ( mti >> 8 );
    arr[1] = 0xFF &   mti;

    return 2;
}
//------------------------------------------------------------------------------
int iso8583_mti_decode(int *mti, const void *data, size_t size, int flags)
{
    /**
     * Decode from raw data.
     *
     * @param mti   The final MTI value read from input data.
     * @param data  The raw data to be read.
     * @param size  Size of the raw data.
     * @param flags Decode options, see ::iso8583_flags_t for more information.
     *
     * @retval Positive Size of data (including zero) read from the input data.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
    if( !mti || !data ) return ISO8583_ERR_INVALID_ARG;
    if( size < 2 ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    const uint8_t *arr = data;
    *mti = ( arr[0] << 8 ) | arr[1];

    return 2;
}
//------------------------------------------------------------------------------
