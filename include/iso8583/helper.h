/**
 * @file
 * @brief     ISO 8583 library high level encapsulated operations.
 * @author    王文佑
 * @date      2015.10.06
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_HELPER_H_
#define _ISO8583_HELPER_H_

#include <stdbool.h>
#include <stdint.h>
#include "fields.h"

#ifdef __cplusplus
extern "C" {
#endif

ISO8583_API(bool) iso8583_helper_check_mti(int resp, int req);

ISO8583_API(bool) iso8583_helper_set_bin(iso8583_fields_t *fields, int id, const void *data, size_t size);

ISO8583_API(uint64_t) iso8583_helper_get_int(const iso8583_fields_t *fields, int id, uint64_t errval);
ISO8583_API(bool)     iso8583_helper_set_int(      iso8583_fields_t *fields, int id, uint64_t value);

ISO8583_API(char*) iso8583_helper_get_str(const iso8583_fields_t *fields, int id, char *buf, size_t bufsz);
ISO8583_API(bool)  iso8583_helper_set_str(      iso8583_fields_t *fields, int id, const char *str);

ISO8583_API(unsigned) iso8583_helper_get_proccode(const iso8583_fields_t *fields);
ISO8583_API(void)     iso8583_helper_set_proccode(      iso8583_fields_t *fields, unsigned proccode);

ISO8583_API(unsigned) iso8583_helper_get_stan(const iso8583_fields_t *fields);
ISO8583_API(void)     iso8583_helper_set_stan(      iso8583_fields_t *fields, unsigned stan);

ISO8583_API(void) iso8583_helper_set_local_datetime(iso8583_fields_t *fields, long long uxtime);

ISO8583_API(char*) iso8583_helper_get_respcode(const iso8583_fields_t *fields, char respcode[2+1]);
ISO8583_API(bool)  iso8583_helper_set_respcode(      iso8583_fields_t *fields, const char *respcode);

ISO8583_API(char*) iso8583_helper_get_terminal_id(const iso8583_fields_t *fields, char id[8+1]);
ISO8583_API(bool)  iso8583_helper_set_terminal_id(      iso8583_fields_t *fields, const char *id);

ISO8583_API(char*) iso8583_helper_get_merchant_id(const iso8583_fields_t *fields, char id[15+1]);
ISO8583_API(bool)  iso8583_helper_set_merchant_id(      iso8583_fields_t *fields, const char *id);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{
/// Encapsulated helper.
namespace helper
{

inline
bool CheckMTI(int resp, int req)
{
    /// @see ::iso8583_helper_check_mti
    return iso8583_helper_check_mti(resp, req);
}

inline
uint64_t GetInteger(const TFields &fields, int id, uint64_t errval)
{
    /// @see ::iso8583_helper_get_int
    return iso8583_helper_get_int(fields.cptr(), id, errval);
}

inline
bool SetInteger(TFields &fields, int id, uint64_t value)
{
    /// @see ::iso8583_helper_set_int
    return iso8583_helper_set_int(fields.cptr(), id, value);
}

inline
std::string GetString(const TFields &fields, int id)
{
    /// @see ::iso8583_helper_get_str
    char buf[8192];
    return iso8583_helper_get_str(fields.cptr(), id, buf, sizeof(buf));
}

inline
bool SetString(TFields &fields, int id, const std::string &str)
{
    /// @see ::iso8583_helper_set_str
    return iso8583_helper_set_str(fields.cptr(), id, str.c_str());
}

inline
unsigned GetProcCode(const TFields &fields)
{
    /// @see ::iso8583_helper_get_proccode
    return iso8583_helper_get_proccode(fields.cptr());
}

inline void SetProcCode(TFields &fields, unsigned proccode)
{
    /// @see ::iso8583_helper_set_proccode
    iso8583_helper_set_proccode(fields.cptr(), proccode);
}

inline
unsigned GetSTAN(const TFields &fields)
{
    /// @see ::iso8583_helper_get_stan
    return iso8583_helper_get_stan(fields.cptr());
}

inline
void SetSTAN(TFields &fields, unsigned stan)
{
    /// @see ::iso8583_helper_set_stan
    iso8583_helper_set_stan(fields.cptr(), stan);
}

inline
void SetLocalDateTime(TFields &fields, long long uxtime)
{
    /// @see ::iso8583_helper_set_local_datetime
    iso8583_helper_set_local_datetime(fields.cptr(), uxtime);
}

inline
std::string GetRespCode(const TFields &fields)
{
    /// @see ::iso8583_helper_get_respcode
    char buf[2+1];
    return iso8583_helper_get_respcode(fields.cptr(), buf);
}

inline
bool SetRespCode(TFields &fields, const std::string &respcode)
{
    /// @see ::iso8583_helper_set_respcode
    return iso8583_helper_set_respcode(fields.cptr(), respcode.c_str());
}

inline
std::string GetTerminalID(const TFields &fields)
{
    /// @see ::iso8583_helper_get_terminal_id
    char buf[8+1];
    return iso8583_helper_get_terminal_id(fields.cptr(), buf);
}

inline
bool SetTerminalID(TFields &fields, const std::string &id)
{
    /// @see ::iso8583_helper_set_terminal_id
    return iso8583_helper_set_terminal_id(fields.cptr(), id.c_str());
}

inline
std::string GetMerchantID(const TFields &fields)
{
    /// @see ::iso8583_helper_get_merchant_id
    char buf[15+1];
    return iso8583_helper_get_merchant_id(fields.cptr(), buf);
}

inline
bool SetMerchantID(TFields &fields, const std::string &id)
{
    /// @see ::iso8583_helper_set_merchant_id
    return iso8583_helper_set_merchant_id(fields.cptr(), id.c_str());
}

}  // namespace helper
}  // namespace ISO8583
#endif  // __cplusplus

#endif
