/**
 * @file
 * @brief     ISO 8583 message type indicator.
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_MTI_H_
#define _ISO8583_MTI_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int iso8583_mti_make(int ver, int cla, int fun, int ori);

int iso8583_mti_encode(int mti, void *buf, size_t size, int flags);
int iso8583_mti_decode(int mti, const void *data, size_t size, int flags);

int iso8583_mti_get_version (int mti);
int iso8583_mti_get_class   (int mti);
int iso8583_mti_get_function(int mti);
int iso8583_mti_get_origin  (int mti);

int iso8583_mti_set_version (int mti, int ver);
int iso8583_mti_set_class   (int mti, int cla);
int iso8583_mti_set_function(int mti, int fun);
int iso8583_mti_set_origin  (int mti, int ori);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
