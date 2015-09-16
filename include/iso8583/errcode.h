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
extern "C" {
#endif

enum
{
    ISO8583_ERR_SUCCESS = 0,
};

static inline
const char* iso8583_err_get_description(int errcode)
{
}

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
