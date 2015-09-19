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

#include <string.h>
#include "errcode.h"
#include "flags.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ISO8583_FITEM_ID_INVALID   0
#define ISO8583_FITEM_ID_MIN       2
#define ISO8583_FITEM_ID_MAX     128

/**
 * @class iso8583_fitem_t
 * @brief Field item.
 */
typedef struct iso8583_fitem_t
{
    /*
     * WARNING : All members are private.
     */
    int     id;  // Field item ID is item index in ISO 8583 bitmap.
    void   *data;
    size_t  size;
} iso8583_fitem_t;

void iso8583_fitem_init      (iso8583_fitem_t *obj);
void iso8583_fitem_init_value(iso8583_fitem_t *obj, int id, const void *data, size_t size);
void iso8583_fitem_init_clone(iso8583_fitem_t *obj, const iso8583_fitem_t *src);
void iso8583_fitem_init_move (iso8583_fitem_t *obj, iso8583_fitem_t *src);
void iso8583_fitem_deinit    (iso8583_fitem_t *obj);

void iso8583_fitem_clone   (iso8583_fitem_t *obj, const iso8583_fitem_t *src);
void iso8583_fitem_movefrom(iso8583_fitem_t *obj, iso8583_fitem_t *src);

int iso8583_fitem_encode(const iso8583_fitem_t *obj, void *buf, size_t size, int flags);
int iso8583_fitem_decode(      iso8583_fitem_t *obj, const void *data, size_t size, int flags, int id);

void iso8583_fitem_clean(iso8583_fitem_t *obj);

int  iso8583_fitem_get_id(const iso8583_fitem_t *obj);
void iso8583_fitem_set_id(      iso8583_fitem_t *obj, int id);

const void* iso8583_fitem_get_data(const iso8583_fitem_t *obj);
size_t      iso8583_fitem_get_size(const iso8583_fitem_t *obj);
void        iso8583_fitem_set_data(const iso8583_fitem_t *obj, const void *data, size_t size);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

/**
 * @brief C++ wrapper of iso8583_fitem_t.
 */
class TFitem : protected iso8583_fitem_t
{
    friend class TFields;

public:
    TFitem()                                      { iso8583_fitem_init      (this); }                      ///< @see iso8583_fitem_t::iso8583_fitem_init
    TFitem(int id, const void *data, size_t size) { iso8583_fitem_init_value(this, id, data, size); }      ///< @see iso8583_fitem_t::iso8583_fitem_init_value
    TFitem(const TFitem &src)                     { iso8583_fitem_init_clone(this, &src); }                ///< @see iso8583_fitem_t::iso8583_fitem_init_clone
#if __cplusplus >= 201103L
    TFitem(TFitem &&src)                          { iso8583_fitem_init_move (this, &src); }                ///< @see iso8583_fitem_t::iso8583_fitem_init_move
#endif
    ~TFitem()                                     { iso8583_fitem_deinit    (this); }                      ///< @see iso8583_fitem_t::iso8583_fitem_deinit

    TFitem& operator=(const TFitem &src)          { iso8583_fitem_clone     (this, &src); return *this; }  ///< @see iso8583_fitem_t::iso8583_fitem_clone
#if __cplusplus >= 201103L
    TFitem& operator=(TFitem &&src)               { iso8583_fitem_movefrom  (this, &src); return *this; }  ///< @see iso8583_fitem_t::iso8583_fitem_movefrom
#endif

public:
    int Encode(void *buf, size_t size, int flags)          const { return iso8583_fitem_encode(this, buf, size, flags); }       ///< @see iso8583_fitem_t::iso8583_fitem_encode
    int Decode(const void *data, size_t size, int flags, int id) { return iso8583_fitem_decode(this, data, size, flags, id); }  ///< @see iso8583_fitem_t::iso8583_fitem_decode

    int  GetID() const { return iso8583_fitem_get_id(this); }      ///< @see iso8583_fitem_t::iso8583_fitem_get_id
    void SetID(int id) {        iso8583_fitem_set_id(this, id); }  ///< @see iso8583_fitem_t::iso8583_fitem_set_id

    const void* GetData()                        const { return iso8583_fitem_get_data(this); }              ///< @see iso8583_fitem_t::iso8583_fitem_get_data
    size_t      GetSize()                        const { return iso8583_fitem_get_size(this); }              ///< @see iso8583_fitem_t::iso8583_fitem_get_size
    void        SetData(const void *data, size_t size) {        iso8583_fitem_set_data(this, data, size); }  ///< @see iso8583_fitem_t::iso8583_fitem_set_data

public:
    bool operator==(const TFitem &tar) { return id == tar.id && size == tar.size && !memcmp(data, tar.data, tar.size); }  ///< Comparison.
    bool operator!=(const TFitem &tar) { return id != tar.id || size != tar.size ||  memcmp(data, tar.data, tar.size); }  ///< Comparison.

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
