#include "mti.h"

//------------------------------------------------------------------------------
int iso8583_mti_make(int ver, int cla, int fun, int ori)
{
    /**
     * Make a MTI value.
     *
     * @param ver ISO 8583 version value.
     * @param cla ISO 8583 class value.
     * @param fun ISO 8583 function value.
     * @param ori ISO 8583 origin value.
     * @return The final MTI value.
     */
#warning Not finished!
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
     * @param flags Encode options, see flags.h for more information.
     *
     * @retval Positive Size of data (including zero) filled to the output buffer.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
#warning Not finished!
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
     * @param flags Decode options, see flags.h for more information.
     *
     * @retval Positive Size of data (including zero) read from the input data.
     * @retval Negative An error code indicates that an error occurred during the process,
     *         see ::iso8583_err_t for more information.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_get_version(int mti)
{
    /**
     * Get ISO 8583 version value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 version value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_get_class(int mti)
{
    /**
     * Get ISO 8583 class value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 class value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_get_function(int mti)
{
    /**
     * Get ISO 8583 function value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 function value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_get_origin(int mti)
{
    /**
     * Get ISO 8583 origin value from MTI.
     *
     * @param mti The current MTI value.
     * @return ISO 8583 origin value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_set_version(int mti, int ver)
{
    /**
     * Set ISO 8583 version value to MTI.
     *
     * @param mti The current MTI value.
     * @param ver The version value to be set.
     * @return The final MTI value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_set_class(int mti, int cla)
{
    /**
     * Set ISO 8583 class value to MTI.
     *
     * @param mti The current MTI value.
     * @param cla The class value to be set.
     * @return The final MTI value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_set_function(int mti, int fun)
{
    /**
     * Set ISO 8583 function value to MTI.
     *
     * @param mti The current MTI value.
     * @param fun The function value to be set.
     * @return The final MTI value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_mti_set_origin(int mti, int ori)
{
    /**
     * Set ISO 8583 origin value to MTI.
     *
     * @param mti The current MTI value.
     * @param ori The origin value to be set.
     * @return The final MTI value.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
