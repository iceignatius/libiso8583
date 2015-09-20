#include <stdlib.h>
#include <stdio.h>
#include <gen/bcd.h>
#include <gen/bufstm.h>
#include "lvar.h"

//------------------------------------------------------------------------------
static
int llvar_write_header(uint8_t buf[3+1], size_t value, finfo_eletype_t eletype, int flags)
{
    if( value > 99 ) return ISO8583_ERR_LVAR_TOO_LONG;

    if( ( flags & ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS ) &&
        !( eletype & ~FINFO_ELE_N ) )
    {
        value <<= 1;
        if( value > 99 ) return ISO8583_ERR_LVAR_TOO_LONG;
    }

    if( flags & ISO8583_FLAG_LVAR_COMPRESSED )
    {
        bcd_encode(buf, 1, value);
        return 1;
    }
    else
    {
        snprintf((char*)buf, 2+1, "%02u", (unsigned)value);
        return 2;
    }
}
//------------------------------------------------------------------------------
static
int lllvar_write_header(uint8_t buf[3+1], size_t value, finfo_eletype_t eletype, int flags)
{
    if( value > 9999 ) return ISO8583_ERR_LVAR_TOO_LONG;

    if( ( flags & ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS ) &&
        !( eletype & ~FINFO_ELE_N ) )
    {
        value <<= 1;
        if( value > 9999 ) return ISO8583_ERR_LVAR_TOO_LONG;
    }

    if( flags & ISO8583_FLAG_LVAR_COMPRESSED )
    {
        bcd_encode(buf, 2, value);
        return 2;
    }
    else
    {
        snprintf((char*)buf, 3+1, "%03u", (unsigned)value);
        return 3;
    }
}
//------------------------------------------------------------------------------
static
int lvar_write_header(uint8_t         buf[3+1],
                      size_t          value,
                      finfo_eletype_t eletype,
                      finfo_lenmode_t lvartype,
                      int             flags)
{
    switch( lvartype )
    {
    case FINFO_LEN_LLVAR  :  return llvar_write_header(buf, value, eletype, flags);
    case FINFO_LEN_LLLVAR :  return lllvar_write_header(buf, value, eletype, flags);
    default               :  return ISO8583_ERR_INVALID_ARG;
    }
}
//------------------------------------------------------------------------------
int lvar_encode(void           *buf,
                size_t          bufsz,
                const void     *data,
                size_t          datsz,
                finfo_eletype_t eletype,
                finfo_lenmode_t lvartype,
                size_t          maxsize,
                int             flags)
{
    if( !buf || !data ) return ISO8583_ERR_INVALID_ARG;

    if( !( flags & ISO8583_FLAG_LVAR_LEN_NO_LIMIT ) &&
        datsz > maxsize )
    {
        return ISO8583_ERR_LVAR_TOO_LONG;
    }

    uint8_t hdr[3+1];
    int     hdrsz = lvar_write_header(hdr, datsz, eletype, lvartype, flags);
    if( hdrsz < 0 ) return ISO8583_ERR_INVALID_ARG;

    bufostm_t stream;
    bufostm_init(&stream, buf, bufsz);

    if( !bufostm_write(&stream, hdr , hdrsz) ) return ISO8583_ERR_BUF_NOT_ENOUGH;
    if( !bufostm_write(&stream, data, datsz) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    return bufostm_get_datasize(&stream);
}
//------------------------------------------------------------------------------
static
int llvar_read_header(bufistm_t       *stream,
                      size_t          *value,
                      finfo_eletype_t  eletype,
                      int              flags)
{
    if( flags & ISO8583_FLAG_LVAR_COMPRESSED )
    {
        uint8_t hdr[1];
        if( !bufistm_read(stream, hdr, 1) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

        *value = bcd_decode(hdr, 1);
    }
    else
    {
        char hdr[2+1] = {0};
        if( !bufistm_read(stream, hdr, 2) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

        char *readend;
        *value = strtoul(hdr, &readend, 10);
        if( *readend ) return ISO8583_ERR_LVAR_HDR_FORMAT;
    }

    if( *value > 99 ) return ISO8583_ERR_LVAR_TOO_LONG;

    if( ( flags & ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS ) &&
        !( eletype & ~FINFO_ELE_N ) )
    {
        *value = ( *value + 1 ) >> 1;
    }

    return bufistm_get_readsize(stream);
}
//------------------------------------------------------------------------------
static
int lllvar_read_header(bufistm_t       *stream,
                       size_t          *value,
                       finfo_eletype_t  eletype,
                       int              flags)
{
    if( flags & ISO8583_FLAG_LVAR_COMPRESSED )
    {
        uint8_t hdr[2];
        if( !bufistm_read(stream, hdr, 2) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

        *value = bcd_decode(hdr, 2);
    }
    else
    {
        char hdr[3+1] = {0};
        if( !bufistm_read(stream, hdr, 3) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

        char *readend;
        *value = strtoul(hdr, &readend, 10);
        if( *readend ) return ISO8583_ERR_LVAR_HDR_FORMAT;
    }

    if( *value > 9999 ) return ISO8583_ERR_LVAR_TOO_LONG;

    if( ( flags & ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS ) &&
        !( eletype & ~FINFO_ELE_N ) )
    {
        *value = ( *value + 1 ) >> 1;
    }

    return bufistm_get_readsize(stream);
}
//------------------------------------------------------------------------------
static
int lvar_read_header(bufistm_t       *stream,
                     size_t          *value,
                     finfo_eletype_t  eletype,
                     finfo_lenmode_t  lvartype,
                     int              flags)
{
    switch( lvartype )
    {
    case FINFO_LEN_LLVAR  :  return llvar_read_header (stream, value, eletype, flags);
    case FINFO_LEN_LLLVAR :  return lllvar_read_header(stream, value, eletype, flags);
    default               :  return ISO8583_ERR_INVALID_ARG;
    }
}
//------------------------------------------------------------------------------
int lvar_decode(void           *buf,
                size_t          bufsz,
                const void     *data,
                size_t          datsz,
                finfo_eletype_t eletype,
                finfo_lenmode_t lvartype,
                size_t          maxsize,
                int             flags)
{
    if( !buf || !data ) return ISO8583_ERR_INVALID_ARG;

    bufistm_t stream;
    bufistm_init(&stream, data, datsz);

    size_t hdrval;
    int hdrsz = lvar_read_header(&stream, &hdrval, eletype, lvartype, flags);
    if( hdrsz < 0 ) return hdrsz;

    if( bufsz < hdrval ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    if( !( flags & ISO8583_FLAG_LVAR_LEN_NO_LIMIT ) &&
        hdrval > maxsize )
    {
        return ISO8583_ERR_LVAR_TOO_LONG;
    }

    if( !bufistm_read(&stream, buf, hdrval) ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    return bufistm_get_readsize(&stream);
}
//------------------------------------------------------------------------------
