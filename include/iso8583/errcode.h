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
    ISO8583_ERR_SUCCESS         =  0,  ///< Success, no error.

    /*
     * WARNING: All error codes must be negative value.
     */

    ISO8583_ERR_GENERAL         = -1,  ///< General or unknown error.
    ISO8583_ERR_INVALID_ARG     = -2,  ///< Invalid argument.
    ISO8583_ERR_BUF_NOT_ENOUGH  = -3,  ///< Buffer size too small.
    ISO8583_ERR_MSG_TOO_LONG    = -4,  ///< Total message too long.
    ISO8583_ERR_SIZEHDR_FAILED  = -5,  ///< Size header verification failed.
    ISO8583_ERR_LVAR_TOO_LONG   = -6,  ///< LVAR payload size too long.
    ISO8583_ERR_LVAR_HDR_FORMAT = -7,  ///< LVAR header value unrecognised.

};

static inline
const char* iso8583_err_get_description(int errcode)
{
    /**
     * Get the corresponding description string of an error code.
     */
#warning Not finished!
    return "Unknown error occurred!";
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{
/// Error code.
namespace err
{

inline std::string GetDescription(int errcode) { return iso8583_err_get_description(errcode); }  ///< @see ::iso8583_err_get_description

}  // namespace err
}  // namespace ISO8583
#endif  // __cplusplus

#endif
