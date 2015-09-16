/**
 * @file
 * @brief     ISO 8583 general field item.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_FITEM_H_
#define _ISO8583_FITEM_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ISO8583_FITEM_ID_INVALID 0
#define ISO8583_FITEM_ID_MAX     128

typedef struct iso8583_fitem_t
{
    /*
     * WARNING : All members are private.
     */
    unsigned  id;  // Field item ID is item index in ISO 8583 bitmap.
    void     *data;
    size_t    size;
} iso8583_fitem_t;

void iso8583_fitem_init      (iso8583_fitem_t *obj);
void iso8583_fitem_init_clone(iso8583_fitem_t *obj, const iso8583_fitem_t *src);
void iso8583_fitem_init_move (iso8583_fitem_t *obj, iso8583_fitem_t *src);
void iso8583_fitem_deinit    (iso8583_fitem_t *obj);

int iso8583_fitem_encode(const iso8583_fitem_t *obj, void *buf, size_t size, int flags);
int iso8583_fitem_decode(      iso8583_fitem_t *obj, const void *data, size_t size, int flags);

unsigned iso8583_fitem_get_id(const iso8583_fitem_t *obj);
void     iso8583_fitem_set_id(      iso8583_fitem_t *obj, unsigned id);

const void* iso8583_fitem_get_data(const iso8583_fitem_t *obj);
size_t      iso8583_fitem_get_size(const iso8583_fitem_t *obj);
void        iso8583_fitem_set_data(const iso8583_fitem_t *obj, const void *data, size_t size);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
