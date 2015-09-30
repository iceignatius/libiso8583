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
#pragma pack(push,8)
typedef struct iso8583_t
{
    /*
     * WARNING : All members are private.
     */
    iso8583_tpdu_t   tpdu;
    int              mti;
    iso8583_fields_t fields;
} iso8583_t;
#pragma pack(pop)

ISO8583_API(void) iso8583_init      (iso8583_t *obj);
ISO8583_API(void) iso8583_init_clone(iso8583_t *obj, const iso8583_t *src);
ISO8583_API(void) iso8583_init_move (iso8583_t *obj, iso8583_t *src);
ISO8583_API(void) iso8583_deinit    (iso8583_t *obj);

ISO8583_API(void) iso8583_clone   (iso8583_t *obj, const iso8583_t *src);
ISO8583_API(void) iso8583_movefrom(iso8583_t *obj, iso8583_t *src);

ISO8583_API(int) iso8583_encode(const iso8583_t *obj, void *buf, size_t size, int flags);
ISO8583_API(int) iso8583_decode(      iso8583_t *obj, const void *data, size_t size, int flags);

ISO8583_API(void) iso8583_clean(iso8583_t *obj);

ISO8583_API(int ) iso8583_get_mti(const iso8583_t *obj);
ISO8583_API(void) iso8583_set_mti(      iso8583_t *obj, int mti);

static inline
iso8583_tpdu_t* iso8583_get_tpdu(iso8583_t *obj)
{
    /// @memberof iso8583_t
    /// @brief Get TPDU object.
    return &obj->tpdu;
}

static inline
const iso8583_tpdu_t* iso8583_get_ctpdu(const iso8583_t *obj)
{
    /// @memberof iso8583_t
    /// @brief Get TPDU object.
    return &obj->tpdu;
}

static inline
iso8583_fields_t* iso8583_get_fields(iso8583_t *obj)
{
    /// @memberof iso8583_t
    /// @brief Get fields container.
    return &obj->fields;
}

static inline
const iso8583_fields_t* iso8583_get_cfields(const iso8583_t *obj)
{
    /// @memberof iso8583_t
    /// @brief Get fields container.
    return &obj->fields;
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

/**
 * @brief C++ wrapper of iso8583_t.
 */
class TISO8583 : protected iso8583_t
{
public:
    TISO8583()                               { iso8583_init      (this); }                    ///< @see iso8583_t::iso8583_init
    TISO8583(const TISO8583 &src)            { iso8583_init_clone(this, &src); }              ///< @see iso8583_t::iso8583_init_clone
#if __cplusplus >= 201103L
    TISO8583(TISO8583 &&src)                 { iso8583_init_move (this, &src); }              ///< @see iso8583_t::iso8583_init_move
#endif
    ~TISO8583()                              { iso8583_deinit    (this); }                    ///< @see iso8583_t::iso8583_deinit

    TISO8583& operator=(const TISO8583 &src) { iso8583_clone   (this, &src); return *this; }  ///< @see iso8583_t::iso8583_clone
#if __cplusplus >= 201103L
    TISO8583& operator=(TISO8583 &&src)      { iso8583_movefrom(this, &src); return *this; }  ///< @see iso8583_t::iso8583_movefrom
#endif

public:
    int Encode(void *buf, size_t size, int flags)  const { return iso8583_encode(this, buf, size, flags); }   ///< @see iso8583_t::iso8583_encode
    int Decode(const void *data, size_t size, int flags) { return iso8583_decode(this, data, size, flags); }  ///< @see iso8583_t::iso8583_decode

    int  GetMTI()  const { return iso8583_get_mti(this); }       ///< @see iso8583_t::iso8583_get_mti
    void SetMTI(int mti) {        iso8583_set_mti(this, mti); }  ///< @see iso8583_t::iso8583_set_mti

    TTPDU&       TPDU()       { return * static_cast<      TTPDU*>( iso8583_get_tpdu (this) ); }  ///< Get TPDU.
    const TTPDU& TPDU() const { return * static_cast<const TTPDU*>( iso8583_get_ctpdu(this) ); }  ///< Get TPDU.

    TFields&       Fields()       { return * static_cast<      TFields*>( iso8583_get_fields (this) ); }  ///< Get fields.
    const TFields& Fields() const { return * static_cast<const TFields*>( iso8583_get_cfields(this) ); }  ///< Get fields.

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
