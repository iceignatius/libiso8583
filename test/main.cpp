#include <assert.h>
#include <stdint.h>
#include "iso8583/iso8583.h"

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

int main(int argc, char *argv[])
{
    test_tpdu();
    test_mti();

    return 0;
}
