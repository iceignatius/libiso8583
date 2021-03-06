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
 *
 * @remarks We redefine the message block to that
 *          the bitmap will be part of data fields.
 *          Or it will be hard to encapsulate the
 *          encode and decode operations for field items.
 */
#pragma pack(push,8)
typedef struct iso8583_fields_t
{
    /*
     * WARNING : All members are private.
     */
    iso8583_fitem_t items[1+ISO8583_FITEM_ID_MAX];
    unsigned        count;
} iso8583_fields_t;
#pragma pack(pop)

ISO8583_API(void) iso8583_fields_init      (iso8583_fields_t *obj);
ISO8583_API(void) iso8583_fields_init_clone(iso8583_fields_t *obj, const iso8583_fields_t *src);
ISO8583_API(void) iso8583_fields_init_move (iso8583_fields_t *obj, iso8583_fields_t *src);
ISO8583_API(void) iso8583_fields_deinit    (iso8583_fields_t *obj);

ISO8583_API(void) iso8583_fields_clone   (iso8583_fields_t *obj, const iso8583_fields_t *src);
ISO8583_API(void) iso8583_fields_movefrom(iso8583_fields_t *obj, iso8583_fields_t *src);

ISO8583_API(int) iso8583_fields_encode(const iso8583_fields_t *obj, void *buf, size_t size, int flags);
ISO8583_API(int) iso8583_fields_decode(      iso8583_fields_t *obj, const void *data, size_t size, int flags);

ISO8583_API(unsigned              ) iso8583_fields_get_count(const iso8583_fields_t *obj);
ISO8583_API(const iso8583_fitem_t*) iso8583_fields_get_item (const iso8583_fields_t *obj, int id);
ISO8583_API(const iso8583_fitem_t*) iso8583_fields_get_first(const iso8583_fields_t *obj);
ISO8583_API(const iso8583_fitem_t*) iso8583_fields_get_next (const iso8583_fields_t *obj, const iso8583_fitem_t *prev);

ISO8583_API(int ) iso8583_fields_insert(iso8583_fields_t *obj, const iso8583_fitem_t *item);
ISO8583_API(void) iso8583_fields_erase (iso8583_fields_t *obj, int id);
ISO8583_API(void) iso8583_fields_clear (iso8583_fields_t *obj);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

/**
 * @brief C++ wrapper of iso8583_fields_t.
 */
class TFields : protected iso8583_fields_t
{
    friend class TISO8583;

public:
    TFields()                              { iso8583_fields_init      (this); }                      ///< @see iso8583_fields_t::iso8583_fields_init
    TFields(const TFields &src)            { iso8583_fields_init_clone(this, &src); }                ///< @see iso8583_fields_t::iso8583_fields_init_clone
#if __cplusplus >= 201103L
    TFields(TFields &&src)                 { iso8583_fields_init_move (this, &src); }                ///< @see iso8583_fields_t::iso8583_fields_init_move
#endif
    ~TFields()                             { iso8583_fields_deinit    (this); }                      ///< @see iso8583_fields_t::iso8583_fields_deinit

    TFields& operator=(const TFields &src) { iso8583_fields_clone     (this, &src); return *this; }  ///< @see iso8583_fields_t::iso8583_fields_clone
#if __cplusplus >= 201103L
    TFields& operator=(TFields &&src)      { iso8583_fields_movefrom  (this, &src); return *this; }  ///< @see iso8583_fields_t::iso8583_fields_movefrom
#endif

public:
    iso8583_fields_t*       cptr()       { return this; }
    const iso8583_fields_t* cptr() const { return this; }

public:
    static const TFitem& npos()
    {
        /**
         * Get an empty item.
         */
        static iso8583_fitem_t item = {0};
        return *static_cast<TFitem*>(&item);
    }

public:
    int Encode(void *buf, size_t size, int flags)  const { return iso8583_fields_encode(this, buf, size, flags); }   ///< @see iso8583_fields_t::iso8583_fields_encode
    int Decode(const void *data, size_t size, int flags) { return iso8583_fields_decode(this, data, size, flags); }  ///< @see iso8583_fields_t::iso8583_fields_decode

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
        const TFitem *item = static_cast<const TFitem*>( iso8583_fields_get_item(this, id) );
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
        const TFitem* item = static_cast<const TFitem*>( iso8583_fields_get_first(this) );
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
        const TFitem* item = static_cast<const TFitem*>( iso8583_fields_get_next(this, &prev) );
        return item ? *item : npos();
    }

    int  Insert(const TFitem &item) { return iso8583_fields_insert(this, &item); }  ///< @see iso8583_fields_t::iso8583_fields_insert
    void Erase (unsigned id)        {        iso8583_fields_erase (this, id); }     ///< @see iso8583_fields_t::iso8583_fields_erase
    void Clear ()                   {        iso8583_fields_clear (this); }         ///< @see iso8583_fields_t::iso8583_fields_clear

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
