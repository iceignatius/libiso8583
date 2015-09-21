/*
 * ISO 8583 field information table.
 */
#ifndef _ISO8583_FINFO_H_
#define _ISO8583_FINFO_H_

typedef enum finfo_eletype_t
{
    FINFO_ELE_A     = 0x01,
    FINFO_ELE_N     = 0x02,
    FINFO_ELE_S     = 0x04,
    FINFO_ELE_AN    = FINFO_ELE_A | FINFO_ELE_N,
    FINFO_ELE_AS    = FINFO_ELE_A | FINFO_ELE_S,
    FINFO_ELE_NS    = FINFO_ELE_N | FINFO_ELE_S,
    FINFO_ELE_ANS   = FINFO_ELE_A | FINFO_ELE_N | FINFO_ELE_S,
    FINFO_ELE_B     = 0x08,
    FINFO_ELE_Z     = 0x10,
} finfo_eletype_t;

typedef enum finfo_lenmode_t
{
    FINFO_LEN_FIXED,
    FINFO_LEN_LLVAR,
    FINFO_LEN_LLLVAR,
} finfo_lenmode_t;

typedef struct finfo_t
{
    finfo_eletype_t eletype;
    finfo_lenmode_t lenmode;
    int             maxsize;
} finfo_t;

static const finfo_t finfo_list[] =
{
    // Field_ID  Element_type   Length_mode       Maximum_size
              {  0,             0,                  0 },
    /*   1 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,  64 },    // Extend bitmap.
    /*   2 */ {  FINFO_ELE_N  , FINFO_LEN_LLVAR ,  19 },    // Primary account number (PAN).
    /*   3 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   6 },    // Processing code.
    /*   4 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Amount, transaction.
    /*   5 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Amount, settlement.
    /*   6 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Amount, cardholders billing.
    /*   7 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Transmission date & time.
    /*   8 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Amount, cardholders billing fee.
    /*   9 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Conversion rate, settlement.
    /*  10 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Conversion rate, cardholders billing.
    /*  11 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   6 },    // System trace audit number.
    /*  12 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   6 },    // Time, local transaction (hhmmss).
    /*  13 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Date, local transaction (MMDD).
    /*  14 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Date, expiration.
    /*  15 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Date, settlement.
    /*  16 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Date, conversion.
    /*  17 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Date, capture.
    /*  18 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Merchant type.
    /*  19 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Acquiring institution country code.
    /*  20 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // PAN extended, country code.
    /*  21 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Forwarding institution. country code.
    /*  22 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Point of service entry mode.
    /*  23 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Application PAN sequence number.
    /*  24 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Function code (ISO 8583:1993)/Network International identifier (NII).
    /*  25 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   2 },    // Point of service condition code.
    /*  26 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   2 },    // Point of service capture code.
    /*  27 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   1 },    // Authorizing identification response length.
    /*  28 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Amount, transaction fee.
    /*  29 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Amount, settlement fee.
    /*  30 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Amount, transaction processing fee.
    /*  31 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   8 },    // Amount, settlement processing fee.
    /*  32 */ {  FINFO_ELE_N  , FINFO_LEN_LLVAR ,  11 },    // Acquiring institution identification code.
    /*  33 */ {  FINFO_ELE_N  , FINFO_LEN_LLVAR ,  11 },    // Forwarding institution identification code.
    /*  34 */ {  FINFO_ELE_NS , FINFO_LEN_LLVAR ,  28 },    // Primary account number, extended.
    /*  35 */ {  FINFO_ELE_Z  , FINFO_LEN_LLVAR ,  37 },    // Track 2 data.
    /*  36 */ {  FINFO_ELE_N  , FINFO_LEN_LLLVAR, 104 },    // Track 3 data.
    /*  37 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,  12 },    // Retrieval reference number.
    /*  38 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   6 },    // Authorization identification response.
    /*  39 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   2 },    // Response code.
    /*  40 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   3 },    // Service restriction code.
    /*  41 */ {  FINFO_ELE_ANS, FINFO_LEN_FIXED ,   8 },    // Card acceptor terminal identification.
    /*  42 */ {  FINFO_ELE_ANS, FINFO_LEN_FIXED ,  15 },    // Card acceptor identification code.
    /*  43 */ {  FINFO_ELE_ANS, FINFO_LEN_FIXED ,  40 },    // Card acceptor name/location (1-23 address 24-36 city 37-38 state 39-40 country).
    /*  44 */ {  FINFO_ELE_AN , FINFO_LEN_LLVAR ,  25 },    // Additional response data.
    /*  45 */ {  FINFO_ELE_AN , FINFO_LEN_LLVAR ,  76 },    // Track 1 data.
    /*  46 */ {  FINFO_ELE_AN , FINFO_LEN_LLLVAR, 999 },    // Additional data - ISO.
    /*  47 */ {  FINFO_ELE_AN , FINFO_LEN_LLLVAR, 999 },    // Additional data - national.
    /*  48 */ {  FINFO_ELE_AN , FINFO_LEN_LLLVAR, 999 },    // Additional data - private.
    /*  49 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Currency code, transaction.
    /*  50 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Currency code, settlement.
    /*  51 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Currency code, cardholders billing.
    /*  52 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,  64 },    // Personal identification number data.
    /*  53 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Security related control information.
    /*  54 */ {  FINFO_ELE_AN , FINFO_LEN_LLLVAR, 120 },    // Additional amounts.
    /*  55 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved ISO.
    /*  56 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved ISO.
    /*  57 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved national.
    /*  58 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved national.
    /*  59 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved national.
    /*  60 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved national.
    /*  61 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved private.
    /*  62 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved private.
    /*  63 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved private.
    /*  64 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,  16 },    // Message authentication code (MAC).
    /*  65 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,   1 },    // Bitmap, extended.
    /*  66 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   1 },    // Settlement code.
    /*  67 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   2 },    // Extended payment code.
    /*  68 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Receiving institution country code.
    /*  69 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Settlement institution country code.
    /*  70 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   3 },    // Network management information code.
    /*  71 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Message number.
    /*  72 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   4 },    // Message number, last.
    /*  73 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,   6 },    // Date, action (YYMMDD).
    /*  74 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Credits, number.
    /*  75 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Credits, reversal number.
    /*  76 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Debits, number.
    /*  77 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Debits, reversal number.
    /*  78 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Transfer number.
    /*  79 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Transfer, reversal number.
    /*  80 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Inquiries number.
    /*  81 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  10 },    // Authorizations, number.
    /*  82 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Credits, processing fee amount.
    /*  83 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Credits, transaction fee amount.
    /*  84 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Debits, processing fee amount.
    /*  85 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  12 },    // Debits, transaction fee amount.
    /*  86 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Credits, amount.
    /*  87 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Credits, reversal amount.
    /*  88 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Debits, amount.
    /*  89 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Debits, reversal amount.
    /*  90 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  42 },    // Original data elements.
    /*  91 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   1 },    // File update code.
    /*  92 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   2 },    // File security code.
    /*  93 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   5 },    // Response indicator.
    /*  94 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,   7 },    // Service indicator.
    /*  95 */ {  FINFO_ELE_AN , FINFO_LEN_FIXED ,  42 },    // Replacement amounts.
    /*  96 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,  64 },    // Message security code.
    /*  97 */ {  FINFO_ELE_N  , FINFO_LEN_FIXED ,  16 },    // Amount, net settlement.
    /*  98 */ {  FINFO_ELE_ANS, FINFO_LEN_FIXED ,  25 },    // Payee.
    /*  99 */ {  FINFO_ELE_N  , FINFO_LEN_LLVAR ,  11 },    // Settlement institution identification code.
    /* 100 */ {  FINFO_ELE_N  , FINFO_LEN_LLVAR ,  11 },    // Receiving institution identification code.
    /* 101 */ {  FINFO_ELE_ANS, FINFO_LEN_LLVAR ,  17 },    // File name.
    /* 102 */ {  FINFO_ELE_ANS, FINFO_LEN_LLVAR ,  28 },    // Account identification 1.
    /* 103 */ {  FINFO_ELE_ANS, FINFO_LEN_LLVAR ,  28 },    // Account identification 2.
    /* 104 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 100 },    // Transaction description.
    /* 105 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 106 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 107 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 108 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 109 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 110 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 111 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for ISO use.
    /* 112 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 113 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 114 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 115 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 116 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 117 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 118 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 119 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for national use.
    /* 120 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 121 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 122 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 123 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 124 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 125 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 126 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 127 */ {  FINFO_ELE_ANS, FINFO_LEN_LLLVAR, 999 },    // Reserved for private use.
    /* 128 */ {  FINFO_ELE_B  , FINFO_LEN_FIXED ,  64 },    // Message authentication code.
};

#endif
