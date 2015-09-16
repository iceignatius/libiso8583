/**
 * @file
 * @brief     ISO 8583 library error code.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_ERRCODE_H_
#define _ISO8583_ERRCODE_H_

#ifdef __cplusplus
#include <string>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ISO 8583 library error codes.
 */
enum iso8583_err_t
{
    ISO8583_ERR_SUCCESS =  0,  ///< Success, no error.
    ISO8583_ERR_GENERAL = -1,  ///< General or unknown error.
};

static inline
const char* iso8583_err_get_description(int errcode)
{
    /**
     * Get the corresponding description string of an error code.
     */
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{
/// C++ wrapper.
namespace err
{

inline string GetDescription(int errcode) { return iso8583_err_get_description(errcode); }  ///< @see ::iso8583_err_get_description

}  // namespace err
}  // namespace ISO8583
#endif  // __cplusplus

#endif
