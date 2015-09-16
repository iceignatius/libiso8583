/**
 * @file
 * @brief     TPDU.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_TPDU_H_
#define _ISO8583_TPDU_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @class iso8583_tpdu_t
 * @brief TPDU.
 */
typedef struct iso8583_tpdu_t
{
    /*
     * WARNING : All members are private.
     */
    unsigned id;
    unsigned dest;
    unsigned src;
} iso8583_tpdu_t;

void iso8583_tpdu_init(iso8583_tpdu_t *obj);

int iso8583_tpdu_encode(const iso8583_tpdu_t *obj, void *buf, size_t size, int flags);
int iso8583_tpdu_decode(      iso8583_tpdu_t *obj, const void *data, size_t size, int flags);

unsigned iso8583_tpdu_get_id  (const iso8583_tpdu_t *obj);
unsigned iso8583_tpdu_get_dest(const iso8583_tpdu_t *obj);
unsigned iso8583_tpdu_get_src (const iso8583_tpdu_t *obj);

void iso8583_tpdu_set_id  (iso8583_tpdu_t *obj, unsigned id);
void iso8583_tpdu_set_dest(iso8583_tpdu_t *obj, unsigned dest);
void iso8583_tpdu_set_src (iso8583_tpdu_t *obj, unsigned src);

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
