/*
 * ISO 8583 bitmap.
 */
#ifndef _ISO8583_BITMAP_H_
#define _ISO8583_BITMAP_H_

#include <stddef.h>
#include <stdbool.h>
#include "errcode.h"

#define ISO8583_BITMAP_ID_MIN   2
#define ISO8583_BITMAP_ID_MAX 128

typedef struct bitmap_t
{
    bool states[1+ISO8583_BITMAP_ID_MAX];  // Index zero (invalid), and one (extend bitmap) will not be used.
} bitmap_t;

void bitmap_init(bitmap_t *obj);

int bitmap_encode(const bitmap_t *obj, void *buf, size_t size, int flags);
int bitmap_decode(      bitmap_t *obj, const void *data, size_t size, int flags);

bool     bitmap_have_id     (const bitmap_t *obj, unsigned id);
unsigned bitmap_get_first_id(const bitmap_t *obj);
unsigned bitmap_get_next_id (const bitmap_t *obj, unsigned prev_id);

int  bitmap_set_id(bitmap_t *obj, unsigned id);
void bitmap_clean (bitmap_t *obj);

#endif
