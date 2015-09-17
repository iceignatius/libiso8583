#include <stdint.h>
#include "mti.h"

//------------------------------------------------------------------------------
int iso8583_mti_make(int ver, int cla, int fun, int ori)
{
    /**
     * Make a MTI value.
     *
     * @param ver ISO 8583 version value, see ::iso8583_mti_ver_t for more information.
     * @param cla ISO 8583 class value, see ::iso8583_mti_cla_t for more information.
     * @param fun ISO 8583 function value, see ::iso8583_mti_fun_t for more information.
     * @param ori ISO 8583 origin value, see ::iso8583_mti_ori_t for more information.
     * @return The final MTI value.
     */
    return ( ver & ISO8583_MTI_VER_MASK ) |
           ( cla & ISO8583_MTI_CLA_MASK ) |
           ( fun & ISO8583_MTI_FUN_MASK ) |
           ( ori & ISO8583_MTI_ORI_MASK );
}
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
int iso8583_mti_get_version(int mti)
{
    /**
     * Get ISO 8583 version value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 version value, see ::iso8583_mti_ver_t for more information.
     */
    return mti & ISO8583_MTI_VER_MASK;
}
//------------------------------------------------------------------------------
int iso8583_mti_get_class(int mti)
{
    /**
     * Get ISO 8583 class value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 class value, see ::iso8583_mti_cla_t for more information.
     */
    return mti & ISO8583_MTI_CLA_MASK;
}
//------------------------------------------------------------------------------
int iso8583_mti_get_function(int mti)
{
    /**
     * Get ISO 8583 function value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 function value, see ::iso8583_mti_fun_t for more information.
     */
    return mti & ISO8583_MTI_FUN_MASK;
}
//------------------------------------------------------------------------------
int iso8583_mti_get_origin(int mti)
{
    /**
     * Get ISO 8583 origin value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 origin value, see ::iso8583_mti_ori_t for more information.
     */
    return mti & ISO8583_MTI_ORI_MASK;
}
//------------------------------------------------------------------------------
int iso8583_mti_set_version(int mti, int ver)
{
    /**
     * Set ISO 8583 version value to MTI.
     *
     * @param mti The current MTI value.
     * @param ver The version value to be set, see ::iso8583_mti_ver_t for more information.
     * @return The final MTI value.
     */
    return ( mti & ~ISO8583_MTI_VER_MASK ) | ( ver & ISO8583_MTI_VER_MASK );
}
//------------------------------------------------------------------------------
int iso8583_mti_set_class(int mti, int cla)
{
    /**
     * Set ISO 8583 class value to MTI.
     *
     * @param mti The current MTI value.
     * @param cla The class value to be set, see ::iso8583_mti_cla_t for more information.
     * @return The final MTI value.
     */
    return ( mti & ~ISO8583_MTI_CLA_MASK ) | ( cla & ISO8583_MTI_CLA_MASK );
}
//------------------------------------------------------------------------------
int iso8583_mti_set_function(int mti, int fun)
{
    /**
     * Set ISO 8583 function value to MTI.
     *
     * @param mti The current MTI value.
     * @param fun The function value to be set, see ::iso8583_mti_fun_t for more information.
     * @return The final MTI value.
     */
    return ( mti & ~ISO8583_MTI_FUN_MASK ) | ( fun & ISO8583_MTI_FUN_MASK );
}
//------------------------------------------------------------------------------
int iso8583_mti_set_origin(int mti, int ori)
{
    /**
     * Set ISO 8583 origin value to MTI.
     *
     * @param mti The current MTI value.
     * @param ori The origin value to be set, see ::iso8583_mti_ori_t for more information.
     * @return The final MTI value.
     */
    return ( mti & ~ISO8583_MTI_ORI_MASK ) | ( ori & ISO8583_MTI_ORI_MASK );
}
//------------------------------------------------------------------------------
