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

int iso8583_encode(const iso8583_t *obj, void *buf, size_t size, int flags);
int iso8583_decode(      iso8583_t *obj, const void *data, size_t size, int flags);

int  iso8583_get_mti(const iso8583_t *obj);
void iso8583_set_mti(      iso8583_t *obj, int mti);

iso8583_tpdu_t*   iso8583_get_tpdu (iso8583_t *obj);
iso8583_fields_t* iso8583_get_field(iso8583_t *obj);

const iso8583_tpdu_t* iso8583_get_ctpdu(const iso8583_t *obj);
const iso8583_fields_t* iso8583_get_cfield(const iso8583_t *obj);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
