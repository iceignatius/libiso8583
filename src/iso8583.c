#include "iso8583.h"

//------------------------------------------------------------------------------
void iso8583_init(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_init_clone(iso8583_t *obj, const iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor that
     *        construct object and clone values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be clone.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_init_move(iso8583_t *obj, iso8583_t *src)
{
    /**
     * @memberof iso8583_t
     * @brief Constructor that
     *        construct object and move values from the other object.
     *
     * @param obj Object instance.
     * @param src The source object to be moved from.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_deinit(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Destructor.
     *
     * @param obj Object instance.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_encode(const iso8583_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_t
     * @brief Encode to raw data.
     *
     * @param obj   Object instance.
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
int iso8583_decode(iso8583_t *obj, const void *data, size_t size, int flags)
{
    /**
     * @memberof iso8583_t
     * @brief Decode from raw data.
     *
     * @param obj   Object instance.
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
int iso8583_get_mti(const iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get MTI value.
     *
     * @param obj Object instance.
     * @return MTI value of the object.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_set_mti(iso8583_t *obj, int mti)
{
    /**
     * @memberof iso8583_t
     * @brief Set MTI value.
     *
     * @param obj Object instance.
     * @param mti The MIT value to be set.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
iso8583_tpdu_t* iso8583_get_tpdu(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get TPDU.
     *
     * @param obj Object instance.
     * @return The TPDU object.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
iso8583_fields_t* iso8583_get_fields(iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get fields
     *
     * @param obj Object instance.
     * @return The fields object.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
