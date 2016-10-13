#include <stdbool.h>
#include <gen/bcd.h>
#include "panval.h"

//------------------------------------------------------------------------------
static
unsigned count_digits(uint64_t value)
{
    unsigned count = 0;
    while( value )
    {
        value /= 10;
        ++count;
    }

    return count;
}
//------------------------------------------------------------------------------
size_t panval_encode(void *buf, size_t bufsize, uint64_t pan)
{
    /**
     * @brief Encode PAN value.
     * @details Encode number as BCD format,
     *          but adjust left and may append 0xF at the end.
     *
     * @param buf     A buffer to receive the output data.
     * @param bufsize Size of the output buffer.
     * @param pan     The PAN value to be encoded.
     * @return The size of data filled to the output buffer; or
     *         ZERO if buffer too small.
     */
    uint8_t *bufpos = buf;
    if( !bufpos || !bufsize ) return 0;

    unsigned digits = count_digits(pan);
    unsigned fillsize = ( digits + 1 ) >> 1;
    if( !fillsize || fillsize > bufsize ) return 0;

    bool need_append = digits & 1;
    if( need_append ) pan *= 10;
    bcd_encode(bufpos, fillsize, pan);
    if( need_append ) bufpos[fillsize-1] |= 0x0F;

    return fillsize;
}
//------------------------------------------------------------------------------
uint64_t panval_decode(const void *data, size_t size)
{
    /**
     * @brief Decode PAN value.
     * @details Extract number as BCD format,
     *          but may ignore the last digit if it is 0xF.
     *
     * @param data Data of the encoded PAN.
     * @param size size of the input data.
     * @return The value of PAN; or
     *         ZERO if failed.
     */
    if( !data || !size ) return 0;

    const uint8_t *bufpos = data;
    unsigned last_digit = bufpos[size-1] & 0x0F;

    uint64_t pan = bcd_decode(data, size);
    if( last_digit == 0xF )
    {
        pan -= last_digit;
        pan /= 10;
    }

    return pan;
}
//------------------------------------------------------------------------------
