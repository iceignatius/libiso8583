/**
 * @file
 * @brief     ISO 8583 library flags definition.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_FLAGS_H_
#define _ISO8583_FLAGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ISO 8583 encode and decode options.
 */
enum iso8583_flags_t
{
    ISO8583_FLAG_HAVE_TPDU = 1,  ///< Have TPDU message.
};

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
