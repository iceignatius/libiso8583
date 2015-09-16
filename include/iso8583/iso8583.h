/**
 * @file
 * @brief     ISO 8583 message.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_H_
#define _ISO8583_H_

#include "tpdu.h"
#include "mti.h"
#include "fields.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @class iso8583_t
 * @brief ISO 8583 major object class.
 */
typedef struct iso8583_t
{
    /*
     * WARNING : All members are private.
     */
    iso8583_tpdu_t   tpdu;
    int              mti;
    iso8583_fields_t fields;
} iso8583_t;

void iso8583_init      (iso8583_t *obj);
void iso8583_init_clone(iso8583_t *obj, const iso8583_t *src);
void iso8583_init_move (iso8583_t *obj, iso8583_t *src);
void iso8583_deinit    (iso8583_t *obj);

void iso8583_clone   (iso8583_t *obj, const iso8583_t *src);
void iso8583_movefrom(iso8583_t *obj, iso8583_t *src);

int iso8583_encode(const iso8583_t *obj, void *buf, size_t size, int flags);
int iso8583_decode(      iso8583_t *obj, const void *data, size_t size, int flags);

int  iso8583_get_mti(const iso8583_t *obj);
void iso8583_set_mti(      iso8583_t *obj, int mti);

iso8583_tpdu_t*   iso8583_get_tpdu  (iso8583_t *obj);
iso8583_fields_t* iso8583_get_fields(iso8583_t *obj);

static inline
const iso8583_tpdu_t* iso8583_get_ctpdu(const iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get TPDU.
     *
     * @param obj Object instance.
     * @return The TPDU object.
     */
}

static inline
const iso8583_fields_t* iso8583_get_cfields(const iso8583_t *obj)
{
    /**
     * @memberof iso8583_t
     * @brief Get fields.
     *
     * @param obj Object instance.
     * @return The fields object.
     */
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

}  // namespace ISO8583
#endif  // __cplusplus

#endif
