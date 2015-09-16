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

/**
 * @brief C++ wrapper of iso8583_tpdu_t.
 */
class TTPDU : protected iso8583_tpdu_t
{
    friend class TISO8583;

public:
    TTPDU() { iso8583_tpdu_init(this); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_init

public:
    int Encode(void *buf, size_t size, int flags)  const { return iso8583_tpdu_encode(this, buf, size, flags); }   ///< @see iso8583_tpdu_t::iso8583_tpdu_encode
    int Decode(const void *data, size_t size, int flags) { return iso8583_tpdu_decode(this, data, size, flags); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_decode

    unsigned GetID  () const { return iso8583_tpdu_get_id  (this); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_get_id
    unsigned GetDest() const { return iso8583_tpdu_get_dest(this); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_get_dest
    unsigned GetSrc () const { return iso8583_tpdu_get_src (this); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_get_src

    void SetID  (unsigned id)   { iso8583_tpdu_set_id  (this, id); }    ///< @see iso8583_tpdu_t::iso8583_tpdu_set_id
    void SetDest(unsigned dest) { iso8583_tpdu_set_dest(this, dest); }  ///< @see iso8583_tpdu_t::iso8583_tpdu_set_dest
    void SetSrc (unsigned src)  { iso8583_tpdu_set_src (this, src); }   ///< @see iso8583_tpdu_t::iso8583_tpdu_set_src

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
