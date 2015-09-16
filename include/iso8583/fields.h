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

void iso8583_fields_clone   (iso8583_fields_t *obj, const iso8583_fields_t *src);
void iso8583_fields_movefrom(iso8583_fields_t *obj, iso8583_fields_t *src);

int iso8583_fields_encode(const iso8583_fields_t *obj, void *buf, size_t size, int flags);
int iso8583_fields_decode(      iso8583_fields_t *obj, const void *data, size_t size, int flags);

unsigned               iso8583_fields_get_count(const iso8583_fields_t *obj);
const iso8583_fitem_t* iso8583_fields_get_item (const iso8583_fields_t *obj, unsigned id);
const iso8583_fitem_t* iso8583_fields_get_first(const iso8583_fields_t *obj);
const iso8583_fitem_t* iso8583_fields_get_next (const iso8583_fields_t *obj, const iso8583_fitem_t *prev);

int  iso8583_fields_insert(iso8583_fields_t *obj, const iso8583_fitem_t *item);
void iso8583_fields_erase (iso8583_fields_t *obj, unsigned id);
void iso8583_fields_clean (iso8583_fields_t *obj);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

/**
 * @brief C++ wrapper of iso8583_fields_t
 */
class TFields : protected iso8583_fields_t
{
public:
    TFields()                              { iso8583_fields_init      (this); }        ///< @see iso8583_fields_t::iso8583_fields_init
    TFields(const TFields &src)            { iso8583_fields_init_clone(this, &src); }  ///< @see iso8583_fields_t::iso8583_fields_init_clone
#if __cplusplus >= 201103L
    TFields(TFields &&src)                 { iso8583_fields_init_move (this, &src); }  ///< @see iso8583_fields_t::iso8583_fields_init_move
#endif
    ~TFields()                             { iso8583_fields_deinit    (this); }        ///< @see iso8583_fields_t::iso8583_fields_deinit

    TFields& operator=(const TFields &src) { iso8583_fields_clone     (this, &src); }  ///< @see iso8583_fields_t::iso8583_fields_clone
#if __cplusplus >= 201103L
    TFields& operator=(TFields &&src)      { iso8583_fields_movefrom  (this, &src); }  ///< @see iso8583_fields_t::iso8583_fields_movefrom
#endif

public:
    static const TFitem& npos()
    {
        /**
         * Get an empty item.
         */
        static TFitem item;
        return item;
    }

public:
    int Encode(void *buf, size_t size, int flags)  const { return iso8583_fields_encode(this, buf, size, flags); }   ///< @see iso8583_fields_t::iso8583_fields_encode
    int Decode(const void *data, size_t size, int flags) {        iso8583_fields_decode(this, data, size, flags); }  ///< @see iso8583_fields_t::iso8583_fields_decode

    unsigned GetCount() const { return iso8583_fields_get_count(this); }  ///< @see iso8583_fields_t::iso8583_fields_get_count

    const TFitem& GetItem(unsigned id) const
    {
        /**
         * Get field item by ID.
         *
         * @param id The specific ID.
         * @return The corresponding item if succeed;
         *         or an empty item (can use TFields::npos to verify) if not found.
         */
        const iso8583_fitem_t* item = iso8583_fields_get_item(this, id);
        return item ? *item : npos();
    }

    const TFitem& GetFirst() const
    {
        /**
         * Get first field item.
         *
         * @return The corresponding item if succeed;
         *         or an empty item (can use TFields::npos to verify) if not found.
         */
        const iso8583_fitem_t* item = iso8583_fields_get_first(this);
        return item ? *item : npos();
    }

    const TFitem& GetNext(const TFitem &prev) const
    {
        /**
         * Get next field item.
         *
         * @param prev The previous item.
         * @return The corresponding item if succeed;
         *         or an empty item (can use TFields::npos to verify) if not found.
         */
        const iso8583_fitem_t* item = iso8583_fields_get_next(this, &prev);
        return item ? *item : npos();
    }

    int  Insert(const TFitem &item) { return iso8583_fields_insert(this, &item); }  ///< @see iso8583_fields_t::iso8583_fields_insert
    void Erase (unsigned id)        {        iso8583_fields_erase (this, id); }     ///< @see iso8583_fields_t::iso8583_fields_erase
    void Clean ()                   {        iso8583_fields_clean (this); }         ///< @see iso8583_fields_t::iso8583_fields_clean

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
