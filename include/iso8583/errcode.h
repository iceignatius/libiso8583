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
    ISO8583_ERR_SUCCESS          =  0,  ///< Success, no error.

    /*
     * WARNING: All error codes must be negative value.
     */

    ISO8583_ERR_GENERAL          = -1,  ///< General or unknown error.
    ISO8583_ERR_INVALID_ARG      = -2,  ///< Invalid argument!
    ISO8583_ERR_BUF_NOT_ENOUGH   = -3,  ///< Buffer size too small!
    ISO8583_ERR_MSG_TOO_LONG     = -4,  ///< Total message too long!
    ISO8583_ERR_SIZEHDR_FAILED   = -5,  ///< Size header verification failed!
    ISO8583_ERR_INVALID_FIELD_ID = -6,  ///< Invalid field ID!
    ISO8583_ERR_FIELD_SIZE_ERROR = -7,  ///< Size of field item not match to what it should be!
    ISO8583_ERR_LVAR_TOO_LONG    = -8,  ///< LVAR payload size too long!
    ISO8583_ERR_LVAR_HDR_FORMAT  = -9,  ///< LVAR header value unrecognised!

};

static inline
const char* iso8583_err_get_description(int errcode)
{
    /**
     * Get the corresponding description string of an error code.
     */
    switch( errcode )
    {
    case ISO8583_ERR_SUCCESS          :  return "Success, no error.";
    case ISO8583_ERR_GENERAL          :  return "General or unknown error!";
    case ISO8583_ERR_INVALID_ARG      :  return "Invalid argument!";
    case ISO8583_ERR_BUF_NOT_ENOUGH   :  return "Buffer size too small!";
    case ISO8583_ERR_MSG_TOO_LONG     :  return "Total message too long!";
    case ISO8583_ERR_SIZEHDR_FAILED   :  return "Size header verification failed!";
    case ISO8583_ERR_INVALID_FIELD_ID :  return "Invalid field ID!";
    case ISO8583_ERR_FIELD_SIZE_ERROR :  return "Size of field item not match to what it should be!";
    case ISO8583_ERR_LVAR_TOO_LONG    :  return "LVAR payload size too long!";
    case ISO8583_ERR_LVAR_HDR_FORMAT  :  return "LVAR header value unrecognised!";
    }

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
