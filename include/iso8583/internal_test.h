/*
 * Test program that used to test internal objects and functions.
 */
#ifndef _ISO8583_INTERNAL_TEST_H_
#define _ISO8583_INTERNAL_TEST_H_

#ifdef ISO8583_DEBUGTEST

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

ISO8583_API(void) iso8583_internal_test(void);

#ifdef __cplusplus
}  // #extern "C"
#endif

#endif // ISO8583_DEBUGTEST

#endif
