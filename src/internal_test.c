#ifdef ISO8583_DEBUGTEST

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "bitmap.h"
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
void iso8583_internal_test(void)
{
    test_bitmap_case1();
    test_bitmap_case2();
}
//------------------------------------------------------------------------------

#endif
