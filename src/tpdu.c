#include "tpdu.h"

//------------------------------------------------------------------------------
void iso8583_tpdu_init(iso8583_tpdu_t *obj)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Constructor.
     *
     * @param obj Object instance.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
int iso8583_tpdu_encode(const iso8583_tpdu_t *obj, void *buf, size_t size, int flags)
{
    /**
     * @memberof iso8583_tpdu_t
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
int iso8583_tpdu_decode(iso8583_tpdu_t *obj, const void *data, size_t size, int flags)
{
    /**
     * @memberof iso8583_tpdu_t
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
unsigned iso8583_tpdu_get_id(const iso8583_tpdu_t *obj)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Get ID.
     *
     * @param obj Object instance.
     * @return ID of the TPDU.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
unsigned iso8583_tpdu_get_dest(const iso8583_tpdu_t *obj)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Get destination number.
     *
     * @param obj Object instance.
     * @return Destination number of the TPDU.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
unsigned iso8583_tpdu_get_src(const iso8583_tpdu_t *obj)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Get source number.
     *
     * @param obj Object instance.
     * @return Source number of the TPDU.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_tpdu_set_id(iso8583_tpdu_t *obj, unsigned id)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Set ID.
     *
     * @param obj Object instance.
     * @param id  The ID to be set.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_tpdu_set_dest(iso8583_tpdu_t *obj, unsigned dest)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Set destination number.
     *
     * @param obj  Object instance.
     * @param dest The destination number to be set.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
void iso8583_tpdu_set_src(iso8583_tpdu_t *obj, unsigned src)
{
    /**
     * @memberof iso8583_tpdu_t
     * @brief Set source number.
     *
     * @param obj Object instance.
     * @param src The source number to be set.
     */
#warning Not finished!
}
//------------------------------------------------------------------------------
