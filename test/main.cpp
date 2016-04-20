#include <assert.h>
#include <stdint.h>
#include <gen/bufstm.h>
#include "iso8583/internal_test.h"
#include "iso8583/iso8583.h"
#include "iso8583/helper.h"
#include "iso8583/exchange.h"

#ifndef ISO8583_DEBUGTEST
    #error This test program needs to work with ISO8583_DEBUGTEST defined!
#endif

void test_tpdu()
{
    static const uint8_t raw[] = { 0x60, 0x12,0x34, 0x56,0x78 };

    // Encode test.
    {
        ISO8583::TTPDU tpdu;

        tpdu.SetID  (0x60);
        tpdu.SetDest(0x1234);
        tpdu.SetSrc (0x5678);

        uint8_t buf[16] = {0};
        assert( sizeof(raw) == tpdu.Encode(buf, sizeof(buf), ISO8583_FLAG_HAVE_TPDU) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        ISO8583::TTPDU tpdu;

        assert( sizeof(raw) == tpdu.Decode(raw, sizeof(raw), ISO8583_FLAG_HAVE_TPDU) );
        assert( tpdu.GetID()   == 0x60   );
        assert( tpdu.GetDest() == 0x1234 );
        assert( tpdu.GetSrc()  == 0x5678 );
    }
}

void test_mti()
{
    static const int     tar   = 0x1204;
    static const uint8_t raw[] = { 0x12, 0x04 };

    // Combine test.
    {
        assert( tar == ISO8583::mti::Make(ISO8583_MTI_VER_1993, ISO8583_MTI_CLA_FINANCIAL, ISO8583_MTI_FUN_REQUEST, ISO8583_MTI_ORI_OTHER) );

        assert( ISO8583::mti::GetVersion (tar) == ISO8583_MTI_VER_1993      );
        assert( ISO8583::mti::GetClass   (tar) == ISO8583_MTI_CLA_FINANCIAL );
        assert( ISO8583::mti::GetFunction(tar) == ISO8583_MTI_FUN_REQUEST   );
        assert( ISO8583::mti::GetOrigin  (tar) == ISO8583_MTI_ORI_OTHER     );

        int mti = 0;
        mti = ISO8583::mti::SetVersion (mti, ISO8583_MTI_VER_1993);
        mti = ISO8583::mti::SetClass   (mti, ISO8583_MTI_CLA_FINANCIAL);
        mti = ISO8583::mti::SetFunction(mti, ISO8583_MTI_FUN_REQUEST);
        mti = ISO8583::mti::SetOrigin  (mti, ISO8583_MTI_ORI_OTHER);
        assert( mti == tar );
    }

    // Encode test.
    {
        uint8_t buf[16] = {0};
        assert( sizeof(raw) == ISO8583::mti::Encode(tar, buf, sizeof(buf), 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        int mti = 0;
        assert( sizeof(raw) == ISO8583::mti::Decode(mti, raw, sizeof(raw), 0) );
        assert( mti == tar );
    }
}

void test_total_message()
{
    static const uint8_t raw[] =
    {
        // Packet header
        0x00, 0x77,

        // TPDU
        0x60, 0x12, 0x34, 0x56, 0x78,

        // MTI
        0x08, 0x10,

        // Bitmap
        0x70, 0x18, 0x01, 0x00, 0x06, 0xA0, 0x00, 0x08,

        // Field 2
        0x08, 0x40, 0x12, 0x88, 0x18, 0x88, 0x81, 0x88, 0x88,

        // Field 3
        0x00, 0x24, 0x00,

        // Field 4
        0x00, 0x00, 0x00, 0x24, 0x00, 0x00,

        // Field 12
        0x13, 0x15, 0x30,

        // Field 13
        0x12, 0x25,

        // Field 24
        0x02, 0x46,

        // Field 38
        'A', 'P', 'P', '1', '2', '3',

        // Field 39
        '0', '0',

        // Field 41
        'A', 'c', 'c', 'e', 'p', 't', 'o', 'r',

        // Field 43
        'O', 'n', 'e', ' ', 'a', 'd', 'd', 'r', 'e', 's', 's', ' ', 'h', 'e', 'r', 'e', '.', ' ', ' ', ' ', ' ', ' ', ' ',
        'T', 'h', 'e', ' ', 'c', 'i', 't', 'y', '.', ' ', ' ', ' ', ' ',
        'S', 'T',
        'Z', 'H',

        // Field 61
        0x00, 0x21,
        'U','s','e','r',' ','d','e','f','i','n','e','d',' ','m','e','s','s','a','g','e','.',
    };

    static const uint8_t pan      [] = { 0x40, 0x12, 0x88, 0x18, 0x88, 0x81, 0x88, 0x88 };
    static const uint8_t proccode [] = { 0x00, 0x24, 0x00 };
    static const uint8_t amount   [] = { 0x00, 0x00, 0x00, 0x24, 0x00, 0x00 };
    static const uint8_t localtime[] = { 0x13, 0x15, 0x30 };
    static const uint8_t localdate[] = { 0x12, 0x25 };
    static const uint8_t nii      [] = { 0x02, 0x46 };
    static const uint8_t authcode [] = { 'A', 'P', 'P', '1', '2', '3' };
    static const uint8_t respcode [] = { '0', '0' };
    static const uint8_t tid      [] = { 'A', 'c', 'c', 'e', 'p', 't', 'o', 'r' };
    static const uint8_t addr     [] = { 'O', 'n', 'e', ' ', 'a', 'd', 'd', 'r', 'e', 's', 's', ' ', 'h', 'e', 'r', 'e', '.', ' ', ' ', ' ', ' ', ' ', ' ',
                                         'T', 'h', 'e', ' ', 'c', 'i', 't', 'y', '.', ' ', ' ', ' ', ' ',
                                         'S', 'T',
                                         'Z', 'H' };
    static const uint8_t userdata [] = { 'U','s','e','r',' ','d','e','f','i','n','e','d',' ','m','e','s','s','a','g','e','.' };

    // Encode test.
    {
        ISO8583::TISO8583 msg;

        msg.TPDU().SetID  (0x60);
        msg.TPDU().SetDest(0x1234);
        msg.TPDU().SetSrc (0x5678);

        msg.SetMTI(0x0810);

        msg.Fields().Insert(ISO8583::TFitem( 2, pan      , sizeof(pan      )));
        msg.Fields().Insert(ISO8583::TFitem( 3, proccode , sizeof(proccode )));
        msg.Fields().Insert(ISO8583::TFitem( 4, amount   , sizeof(amount   )));
        msg.Fields().Insert(ISO8583::TFitem(12, localtime, sizeof(localtime)));
        msg.Fields().Insert(ISO8583::TFitem(13, localdate, sizeof(localdate)));
        msg.Fields().Insert(ISO8583::TFitem(24, nii      , sizeof(nii      )));
        msg.Fields().Insert(ISO8583::TFitem(38, authcode , sizeof(authcode )));
        msg.Fields().Insert(ISO8583::TFitem(39, respcode , sizeof(respcode )));
        msg.Fields().Insert(ISO8583::TFitem(41, tid      , sizeof(tid      )));
        msg.Fields().Insert(ISO8583::TFitem(43, addr     , sizeof(addr     )));
        msg.Fields().Insert(ISO8583::TFitem(61, userdata , sizeof(userdata )));

        uint8_t buf[512] = {0};
        int flags = ISO8583_FLAG_HAVE_SIZEHDR | ISO8583_FLAG_HAVE_TPDU | ISO8583_FLAG_LVAR_COMPRESSED;
        assert( sizeof(raw) == msg.Encode(buf, sizeof(buf), flags) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        ISO8583::TISO8583 msg;

        int flags = ISO8583_FLAG_HAVE_SIZEHDR | ISO8583_FLAG_HAVE_TPDU | ISO8583_FLAG_LVAR_COMPRESSED;
        assert( sizeof(raw) == msg.Decode(raw, sizeof(raw), flags) );

        assert(   0x60 == msg.TPDU().GetID  () );
        assert( 0x1234 == msg.TPDU().GetDest() );
        assert( 0x5678 == msg.TPDU().GetSrc () );

        assert( 0x0810 == msg.GetMTI() );

        ISO8583::TFitem item;

        item = msg.Fields().GetFirst();
        assert( item == ISO8583::TFitem( 2, pan      , sizeof(pan      )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem( 3, proccode , sizeof(proccode )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem( 4, amount   , sizeof(amount   )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(12, localtime, sizeof(localtime)) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(13, localdate, sizeof(localdate)) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(24, nii      , sizeof(nii      )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(38, authcode , sizeof(authcode )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(39, respcode , sizeof(respcode )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(41, tid      , sizeof(tid      )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(43, addr     , sizeof(addr     )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFitem(61, userdata , sizeof(userdata )) );

        item = msg.Fields().GetNext(item);
        assert( item == ISO8583::TFields::npos() );
    }
}

void test_helper_tools()
{
    ISO8583::TFields fields;
    ISO8583::TFitem item;

    // Integer value read write test.
    {
        fields.Clear();

        assert( ISO8583::helper::SetInteger(fields, 3, 123456) );

        assert( ( item = fields.GetItem(3) ) != fields.npos() );
        assert( item.GetSize() == 3 );
        assert( 0 == memcmp(item.GetData(), "\x12\x34\x56", 3) );

        assert( 123456 == ISO8583::helper::GetInteger(fields, 3, 777) );
        assert(    777 == ISO8583::helper::GetInteger(fields, 4, 777) );
    }

    // String value read write test.
    {
        fields.Clear();

        assert( ISO8583::helper::SetString(fields, 39, "AB") );

        assert( ( item = fields.GetItem(39) ) != fields.npos() );
        assert( item.GetSize() == 2 );
        assert( 0 == memcmp(item.GetData(), "AB", 2) );

        assert( "AB" == ISO8583::helper::GetString(fields, 39) );
        assert( ""   == ISO8583::helper::GetString(fields, 40) );
    }

    // Set local time test.
    {
        fields.Clear();

        ISO8583::helper::SetLocalDateTime(fields, -886141800);  // Time stamp: -886141800, 1941/12/02 17:30.

        assert( ( item = fields.GetItem(13) ) != fields.npos() );
        assert( fields.GetItem(13).GetSize() == 2 );
        assert( 0 == memcmp(item.GetData(), "\x12\x02", 2) );

        assert( ( item = fields.GetItem(12) ) != fields.npos() );
        assert( fields.GetItem(12).GetSize() == 3 );
        assert( 0 == memcmp(item.GetData(), "\x17\x30\x00", 3) );
    }
}

int test_exchange_on_send(bufostm_t *stream, const void *data, size_t size)
{
    if( size > 7 ) size = 7;
    return bufostm_write(stream, data, size) ? size : -1;
}

int test_exchange_on_recv(bufistm_t *stream, void *buf, size_t size)
{
    if( size > 7 ) size = 7;
    return bufistm_read(stream, buf, size) ? size : -1;
}

void test_exchange()
{
    int flags = ISO8583_FLAG_HAVE_SIZEHDR |
                ISO8583_FLAG_HAVE_TPDU    |
                ISO8583_FLAG_LVAR_COMPRESSED;

    ISO8583::TISO8583 sample_msg;
    sample_msg.SetMTI(0x1234);
    ISO8583::helper::SetSTAN(sample_msg.Fields(), 7);

    uint8_t sample_bin[1024];
    int sample_size = sample_msg.Encode(sample_bin, sizeof(sample_bin), flags);
    assert( sample_size > 0 );

    // Send test.
    {
        uint8_t buf[1024];

        bufostm_t stream;
        bufostm_init(&stream, buf, sizeof(buf));

        ISO8583::TExchange exg(flags,
                               &stream,
                               (int(*)(void*,const void*,size_t)) test_exchange_on_send,
                               NULL);

        assert( ISO8583_ERR_SUCCESS == exg.Send(sample_msg, 3*1000) );

        assert( sample_size == (int)bufostm_get_datasize(&stream) );
        assert( 0 == memcmp(buf, sample_bin, sample_size) );
    }

    // Receive test.
    {
        bufistm_t stream;
        bufistm_init(&stream, sample_bin, sample_size);

        ISO8583::TExchange exg(flags,
                               &stream,
                               NULL,
                               (int(*)(void*,void*,size_t)) test_exchange_on_recv);

        ISO8583::TISO8583 msg;
        assert( ISO8583_ERR_SUCCESS == exg.Recv(msg, 3*1000) );

        assert( msg.GetMTI() == sample_msg.GetMTI() );
        assert( ISO8583::helper::GetSTAN(msg.Fields()) == ISO8583::helper::GetSTAN(sample_msg.Fields()) );
    }
}

int main(int argc, char *argv[])
{
    iso8583_internal_test();
    test_tpdu();
    test_mti();
    test_total_message();
    test_helper_tools();
    test_exchange();

    return 0;
}
