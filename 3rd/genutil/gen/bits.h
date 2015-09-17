/**
 * @file
 * @brief     Bits operation.
 * @details   Advanced tools about bits operation.
 * @author    王文佑
 * @date      2015.08.10
 * @copyright ZLib Licence
 * @see       http://www.openfoundry.org/of/projects/2419
 */
#ifndef _GEN_BITS_H_
#define _GEN_BITS_H_

#include <stdint.h>
#include "inline.h"

#ifdef __cplusplus
extern "C" {
#endif

INLINE
int bits_get_bit(const void *bits, unsigned index)
{
    /// Check if the specified bit has set to 1.
    return ( ((uint8_t*)bits)[ index >> 3 ] & ( 0x80 >> ( index & 0x07 ) ) )?( 1 ):( 0 );
}

INLINE
void bits_set_bit(void *bits, unsigned index)
{
    /// Set specified bit to 1.
    ((uint8_t*)bits)[ index >> 3 ] |= ( 0x80 >> ( index & 0x07 ) );
}

INLINE
void bits_clear_bit(void *bits, unsigned index)
{
    /// Set specified bit to 0.
    ((uint8_t*)bits)[ index >> 3 ] &= ~( 0x80 >> ( index & 0x07 ) );
}

INLINE
void bits_set_bit_onoff(void *bits, unsigned index, int on)
{
    if( on )
        bits_set_bit(bits, index);
    else
        bits_clear_bit(bits, index);
}

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
