#include "fitem.h"

//------------------------------------------------------------------------------
void iso8583_fitem_init(iso8583_fitem_t *obj)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_fitem_set_data(const iso8583_fitem_t *obj, const void *data, size_t size)
{
    /**
     * @memberof iso8583_fitem_t
     * @brief Set field data.
     *
     * @param obj  Object instance.
     * @param data The data to be set.
     * @param size Size of the input data.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
