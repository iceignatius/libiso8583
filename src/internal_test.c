#ifdef ISO8583_DEBUGTEST

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "bitmap.h"
#include "lvar.h"
#include "internal_test.h"

//------------------------------------------------------------------------------
static
void test_bitmap_case1(void)
{
    static const uint8_t raw[] = { 0x72,0x34,0x05,0x41,0x28,0xC2,0x88,0x05 };

    // Encode test.
    {
        bitmap_t bmp;
        bitmap_init(&bmp);

        assert( !bitmap_set_id(&bmp,  2) );
        assert( !bitmap_set_id(&bmp,  3) );
        assert( !bitmap_set_id(&bmp,  4) );
        assert( !bitmap_set_id(&bmp,  7) );
        assert( !bitmap_set_id(&bmp, 11) );
        assert( !bitmap_set_id(&bmp, 12) );
        assert( !bitmap_set_id(&bmp, 14) );
        assert( !bitmap_set_id(&bmp, 22) );
        assert( !bitmap_set_id(&bmp, 24) );
        assert( !bitmap_set_id(&bmp, 26) );
        assert( !bitmap_set_id(&bmp, 32) );
        assert( !bitmap_set_id(&bmp, 35) );
        assert( !bitmap_set_id(&bmp, 37) );
        assert( !bitmap_set_id(&bmp, 41) );
        assert( !bitmap_set_id(&bmp, 42) );
        assert( !bitmap_set_id(&bmp, 47) );
        assert( !bitmap_set_id(&bmp, 49) );
        assert( !bitmap_set_id(&bmp, 53) );
        assert( !bitmap_set_id(&bmp, 62) );
        assert( !bitmap_set_id(&bmp, 64) );

        uint8_t buf[64] = {0};
        assert( sizeof(raw) == bitmap_encode(&bmp, buf, sizeof(buf), 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        bitmap_t bmp;
        bitmap_init(&bmp);

        assert( sizeof(raw) == bitmap_decode(&bmp, raw, sizeof(raw), 0) );

        int id = 0;
        id = bitmap_get_first_id(&bmp);     assert( id ==  2 );
        id = bitmap_get_next_id(&bmp, id);  assert( id ==  3 );
        id = bitmap_get_next_id(&bmp, id);  assert( id ==  4 );
        id = bitmap_get_next_id(&bmp, id);  assert( id ==  7 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 11 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 12 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 14 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 22 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 24 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 26 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 32 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 35 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 37 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 41 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 42 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 47 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 49 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 53 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 62 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 64 );
        id = bitmap_get_next_id(&bmp, id);  assert( id ==  0 );
    }
}
//------------------------------------------------------------------------------
static
void test_bitmap_case2(void)
{
    static const uint8_t raw[] =
    {
        0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03
    };

    // Encode test.
    {
        bitmap_t bmp;
        bitmap_init(&bmp);

        assert( !bitmap_set_id(&bmp,  64) );
        assert( !bitmap_set_id(&bmp, 127) );
        assert( !bitmap_set_id(&bmp, 128) );

        uint8_t buf[64] = {0};
        assert( sizeof(raw) == bitmap_encode(&bmp, buf, sizeof(buf), 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        bitmap_t bmp;
        bitmap_init(&bmp);

        assert( sizeof(raw) == bitmap_decode(&bmp, raw, sizeof(raw), 0) );

        int id = 0;
        id = bitmap_get_first_id(&bmp);     assert( id ==  64 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 127 );
        id = bitmap_get_next_id(&bmp, id);  assert( id == 128 );
        id = bitmap_get_next_id(&bmp, id);  assert( id ==   0 );
    }
}
//------------------------------------------------------------------------------
static
void test_lvar_compress_type(void)
{
    // LLVAR, uncompressed.
    {
        static const uint8_t raw[] = { '0','7', 'm','e','s','s','a','g','e' };

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), FINFO_ELE_ANS, FINFO_LEN_LLVAR, 99, 0) );
        assert( 0 == strcmp(buf, "message") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "message", strlen("message"), FINFO_ELE_ANS, FINFO_LEN_LLVAR, 99, 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // LLVAR, compressed.
    {
        static const uint8_t raw[] = { 0x07, 'm','e','s','s','a','g','e' };

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), FINFO_ELE_ANS, FINFO_LEN_LLVAR, 99, ISO8583_FLAG_LVAR_COMPRESSED) );
        assert( 0 == strcmp(buf, "message") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "message", strlen("message"), FINFO_ELE_ANS, FINFO_LEN_LLVAR, 99, ISO8583_FLAG_LVAR_COMPRESSED) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // LLLVAR, uncompressed.
    {
        static const uint8_t raw[] = { '0','0','7', 'm','e','s','s','a','g','e' };

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 99, 0) );
        assert( 0 == strcmp(buf, "message") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "message", strlen("message"), FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 99, 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // LLLVAR, compressed.
    {
        static const uint8_t raw[] = { 0x00,0x07, 'm','e','s','s','a','g','e' };

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 99, ISO8583_FLAG_LVAR_COMPRESSED) );
        assert( 0 == strcmp(buf, "message") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "message", strlen("message"), FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 99, ISO8583_FLAG_LVAR_COMPRESSED) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }
}
//------------------------------------------------------------------------------
static
void test_lvar_size_mode(void)
{
    // Byte mode, ASCII data.
    {
        static const uint8_t raw[] = { 0x05, '1','3','5','7','9' };

        finfo_eletype_t eletype = FINFO_ELE_ANS;
        finfo_lenmode_t lenmode = FINFO_LEN_LLVAR;
        size_t          maxsize = 99;
        int             flags   = ISO8583_FLAG_LVAR_COMPRESSED;

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), eletype, lenmode, maxsize, flags) );
        assert( 0 == strcmp(buf, "13579") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "13579", strlen("13579"), eletype, lenmode, maxsize, flags) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Byte mode, digit data.
    {
        static const uint8_t raw[] = { 0x03, 0x01,0x35,0x79 };
        static const uint8_t pay[] = { 0x01,0x35,0x79 };

        finfo_eletype_t eletype = FINFO_ELE_N;
        finfo_lenmode_t lenmode = FINFO_LEN_LLVAR;
        size_t          maxsize = 99;
        int             flags   = ISO8583_FLAG_LVAR_COMPRESSED;

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), eletype, lenmode, maxsize, flags) );
        assert( 0 == memcmp(buf, pay, sizeof(pay)) );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), pay, sizeof(pay), eletype, lenmode, maxsize, flags) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Element mode, ASCII data.
    {
        static const uint8_t raw[] = { 0x05, '1','3','5','7','9' };

        finfo_eletype_t eletype = FINFO_ELE_ANS;
        finfo_lenmode_t lenmode = FINFO_LEN_LLVAR;
        size_t          maxsize = 99;
        int             flags   = ISO8583_FLAG_LVAR_COMPRESSED | ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS;

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), eletype, lenmode, maxsize, flags) );
        assert( 0 == strcmp(buf, "13579") );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), "13579", strlen("13579"), eletype, lenmode, maxsize, flags) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Element mode, digit data.
    {
        static const uint8_t raw[] = { 0x05, 0x01,0x35,0x79 };
        static const uint8_t pay[] = { 0x01,0x35,0x79 };

        finfo_eletype_t eletype = FINFO_ELE_N;
        finfo_lenmode_t lenmode = FINFO_LEN_LLVAR;
        size_t          maxsize = 99;
        int             flags   = ISO8583_FLAG_LVAR_COMPRESSED | ISO8583_FLAG_LVAR_LEN_IN_ELEMENTS;

        char buf[128] = {0};
        assert( sizeof(raw) == lvar_decode(buf, sizeof(buf), raw, sizeof(raw), eletype, lenmode, maxsize, flags) );
        assert( 0 == memcmp(buf, pay, sizeof(pay)) );

        assert( sizeof(raw) == lvar_encode(buf, sizeof(buf), pay, sizeof(pay), eletype, lenmode, maxsize, flags) );
        static const uint8_t raw_enc[] = { 0x06, 0x01,0x35,0x79 };
        assert( 0 == memcmp(buf, raw_enc, sizeof(raw_enc)) );
    }
}
//------------------------------------------------------------------------------
void iso8583_internal_test(void)
{
    test_bitmap_case1();
    test_bitmap_case2();
    test_lvar_compress_type();
    test_lvar_size_mode();
}
//------------------------------------------------------------------------------

#endif
