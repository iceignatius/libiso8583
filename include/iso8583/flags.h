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
    ISO8583_FLAG_HAVE_SIZEHDR         = 0x01,   ///< Have size header.
    ISO8583_FLAG_HAVE_TPDU            = 0x02,   ///< Have TPDU message.
    ISO8583_FLAG_LVAR_COMPRESSED      = 0x10,   ///< Indicates that the length value of LVAR is
                                                ///< in compressed format (BCD),
                                                ///< not in uncompressed format (ASCII).
    ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS = 0x20,   ///< Indicates that the length value of LVAR means
                                                ///< how many ISO 8583 data elements the payload have,
                                                ///< not how many bytes the payload have.
    ISO8583_FLAG_LVAR_LEN_NO_LIMIT    = 0x40,   ///< Do not check payload length of LVAR object.
};

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
