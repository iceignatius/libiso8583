/**
 * @file
 * @brief     ISO 8583 field item container.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_FIELDS_H_
#define _ISO8583_FIELDS_H_

#include "fitem.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @class iso8583_fields_t
 * @brief Container of field items.
 */
typedef struct iso8583_fields_t
{
    /*
     * WARNING : All members are private.
     */
    iso8583_fitem_t items[1+ISO8583_FITEM_ID_MAX];
    unsigned        count;
} iso8583_fields_t;

void iso8583_fields_init      (iso8583_fields_t *obj);
void iso8583_fields_init_clone(iso8583_fields_t *obj, const iso8583_fields_t *src);
void iso8583_fields_init_move (iso8583_fields_t *obj, iso8583_fields_t *src);
void iso8583_fields_deinit    (iso8583_fields_t *obj);

int iso8583_fields_encode(const iso8583_fields_t *obj, void *buf, size_t size, int flags);
int iso8583_fields_decode(      iso8583_fields_t *obj, const void *data, size_t size, int flags);

unsigned iso8583_fields_get_count(const iso8583_fields_t *obj);

iso8583_fitem_t* iso8583_fields_get_item (iso8583_fields_t *obj, unsigned id);
iso8583_fitem_t* iso8583_fields_get_first(iso8583_fields_t *obj);
iso8583_fitem_t* iso8583_fields_get_next (iso8583_fields_t *obj, const iso8583_fitem_t *prev);

int  iso8583_fields_insert(iso8583_fields_t *obj, const iso8583_fitem_t *item);
void iso8583_fields_erase(iso8583_fields_t *obj, unsigned id);
void iso8583_fields_clean(iso8583_fields_t *obj);

static inline
const iso8583_fitem_t* iso8583_fields_get_citem(const iso8583_fields_t *obj, unsigned id)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get field item by field ID.
     *
     * @param obj Object instance.
     * @param id  The specific field ID.
     * @return The field item if succeed; or NULL if no item be found.
     */
}

static inline
const iso8583_fitem_t* iso8583_fields_get_cfirst(const iso8583_fields_t *obj)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the first field item.
     *
     * @param obj Object instance.
     * @return The field item if succeed; or NULL if no item be found.
     */
}

static inline
const iso8583_fitem_t* iso8583_fields_get_cnext(const iso8583_fields_t *obj, const iso8583_fitem_t *prev)
{
    /**
     * @memberof iso8583_fields_t
     * @brief Get the next field item.
     *
     * @param obj  Object instance.
     * @param prev The previous field item.
     * @return The field item if succeed; or NULL if no item be found.
     */
}


#ifdef __cplusplus
}  // extern "C"
#endif

#endif
