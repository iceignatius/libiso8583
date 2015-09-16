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
#warning Not finished!
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
     * @param src The source object to be clone.
     */
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
}
//------------------------------------------------------------------------------
iso8583_fitem_t* iso8583_fields_get_item(iso8583_fields_t *obj, unsigned id)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get field item by field ID.
     *
     * @param obj Object instance.
     * @param id  The specific field ID.
     * @return The field item if succeed; or NULL if no item be found.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
iso8583_fitem_t* iso8583_fields_get_first(iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the first field item.
     *
     * @param obj Object instance.
     * @return The field item if succeed; or NULL if no item be found.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
iso8583_fitem_t* iso8583_fields_get_next(iso8583_fields_t *obj, const iso8583_fitem_t *prev)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the next field item.
     *
     * @param obj  Object instance.
     * @param prev The previous field item.
     * @return The field item if succeed; or NULL if no item be found.
     */
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
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
#warning Not finished!
}
//------------------------------------------------------------------------------
