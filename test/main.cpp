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
        assert( sizeof(raw) == tpdu.Encode(buf, sizeof(buf), 0) );
        assert( 0 == memcmp(buf, raw, sizeof(raw)) );
    }

    // Decode test.
    {
        ISO8583::TTPDU tpdu;

        assert( sizeof(raw) == tpdu.Decode(raw, sizeof(raw), 0) );
        assert( tpdu.GetID()   == 0x60   );
        assert( tpdu.GetDest() == 0x1234 );
        assert( tpdu.GetSrc()  == 0x5678 );
    }
}

int main(int argc, char *argv[])
{
    test_tpdu();

    return 0;
}
