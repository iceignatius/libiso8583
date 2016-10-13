/*
 * Primary Account Number (PAN) value encoder and decoder.
 */
#ifndef _iso8583par_panval_H_
#define _iso8583par_panval_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t   panval_encode(void *buf, size_t bufsize, uint64_t value);
uint64_t panval_decode(const void *data, size_t size);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
