/*
 * ISO 8583 LLVAR and LLLVAR encoder and decoder.
 */
#ifndef _ISO8583_LVAR_H_
#define _ISO8583_LVAR_H_

#include <stddef.h>
#include "errcode.h"
#include "flags.h"
#include "finfo.h"

int lvar_encode(void           *buf,
                size_t          bufsz,
                const void     *data,
                size_t          datsz,
                finfo_eletype_t eletype,
                finfo_lenmode_t lvartype,
                size_t          maxcount,
                int             flags);

int lvar_decode(void           *buf,
                size_t          bufsz,
                size_t         *fillsz,  // Return data bytes filled to the output buffer.
                const void     *data,
                size_t          datsz,
                finfo_eletype_t eletype,
                finfo_lenmode_t lvartype,
                size_t          maxcount,
                int             flags);

#endif
