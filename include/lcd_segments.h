#pragma once
#include <stdint.h>

// Packed segment ID
// bits 7..2 = HT1621 RAM address
// bits 1..0 = bit index
using SegId = uint8_t;

struct Digit7
{
    SegId A, B, C, D, E, F, G;
};

#define SEG_PACK(addr, bit) static_cast<uint8_t>(((addr) << 2) | ((bit) & 0x03))
#define SEG_ADDR(seg) ((seg) >> 2)
#define SEG_BIT(seg)  ((seg) & 0x03)


// ============================================================
// Special indicators used by the FCU
// ============================================================

// Speed decimal points
constexpr SegId SPD_POINT_1 = SEG_PACK(31,0);
constexpr SegId SPD_POINT_2 = SEG_PACK(29,0);
constexpr SegId SPD_POINT_3 = SEG_PACK(27,0);

// Speed panel
constexpr SegId SPD_LABEL       = SEG_PACK(25, 3); // Z1
constexpr SegId MACH_LABEL      = SEG_PACK(25, 2); // Z2
constexpr SegId SPD_MANAGED_DOT = SEG_PACK(25, 1); // Z19

// Heading panel
constexpr SegId HDG_LABEL           = SEG_PACK(24, 3); // Z3
constexpr SegId TRK_LABEL           = SEG_PACK(22, 3); // Z4
constexpr SegId LAT_LABEL           = SEG_PACK(20, 3); // Z5
constexpr SegId HDG_TRK_MANAGED_DOT = SEG_PACK(18, 2); // Z18

// Mode panel
constexpr SegId MODE_HDG_LABEL = SEG_PACK(18, 3); // Z6
constexpr SegId MODE_TRK_LABEL = SEG_PACK(18, 1); // Z7
constexpr SegId MODE_VS_LABEL  = SEG_PACK(17, 3); // Z8
constexpr SegId MODE_FPA_LABEL = SEG_PACK(18, 0); // Z9

// Altitude panel
constexpr SegId ALT_LABEL_      = SEG_PACK(15, 3); // Z10
constexpr SegId LVLCH_LABEL     = SEG_PACK(6, 3);  // Z11
constexpr SegId ALT_VS_LABEL    = SEG_PACK(10, 3); // Z12
constexpr SegId ALT_FPA_LABEL   = SEG_PACK(12, 3); // Z13
constexpr SegId ALT_MANAGED_DOT = SEG_PACK(4, 3);  // Z16


// Altitude change decimal point
constexpr SegId ALT_CHANGE_POINT = SEG_PACK(8,3);

// Altitude sign
constexpr SegId ALT_MINUS = SEG_PACK(2,3);
constexpr SegId ALT_PLUS_BAR = SEG_PACK(0,3); // plus = ALT_MINUS + ALT_PLUS_BAR


// ============================================================
// Digit definitions (15 digits)
// ============================================================

constexpr Digit7 DIGITS[15] =
{
    { SEG_PACK(30,3), SEG_PACK(30,2), SEG_PACK(30,1), SEG_PACK(30,0), SEG_PACK(31,1), SEG_PACK(31,3), SEG_PACK(31,2) },
    { SEG_PACK(28,3), SEG_PACK(28,2), SEG_PACK(28,1), SEG_PACK(28,0), SEG_PACK(29,1), SEG_PACK(29,3), SEG_PACK(29,2) },
    { SEG_PACK(26,3), SEG_PACK(26,2), SEG_PACK(26,1), SEG_PACK(26,0), SEG_PACK(27,1), SEG_PACK(27,3), SEG_PACK(27,2) },
    { SEG_PACK(23,3), SEG_PACK(23,2), SEG_PACK(23,1), SEG_PACK(23,0), SEG_PACK(24,0), SEG_PACK(24,2), SEG_PACK(24,1) },
    { SEG_PACK(21,3), SEG_PACK(21,2), SEG_PACK(21,1), SEG_PACK(21,0), SEG_PACK(22,0), SEG_PACK(22,2), SEG_PACK(22,1) },
    { SEG_PACK(19,3), SEG_PACK(19,2), SEG_PACK(19,1), SEG_PACK(19,0), SEG_PACK(20,0), SEG_PACK(20,2), SEG_PACK(20,1) },
    { SEG_PACK(16,3), SEG_PACK(16,2), SEG_PACK(16,1), SEG_PACK(16,0), SEG_PACK(17,0), SEG_PACK(17,2), SEG_PACK(17,1) },
    { SEG_PACK(14,3), SEG_PACK(14,2), SEG_PACK(14,1), SEG_PACK(14,0), SEG_PACK(15,0), SEG_PACK(15,2), SEG_PACK(15,1) },
    { SEG_PACK(1,3),  SEG_PACK(1,2),  SEG_PACK(1,1),  SEG_PACK(1,0),  SEG_PACK(0,0),  SEG_PACK(0,2),  SEG_PACK(0,1)  },
    { SEG_PACK(3,3),  SEG_PACK(3,2),  SEG_PACK(3,1),  SEG_PACK(3,0),  SEG_PACK(2,0),  SEG_PACK(2,2),  SEG_PACK(2,1)  },
    { SEG_PACK(5,3),  SEG_PACK(5,2),  SEG_PACK(5,1),  SEG_PACK(5,0),  SEG_PACK(4,0),  SEG_PACK(4,2),  SEG_PACK(4,1)  },
    { SEG_PACK(7,3),  SEG_PACK(7,2),  SEG_PACK(7,1),  SEG_PACK(7,0),  SEG_PACK(6,0),  SEG_PACK(6,2),  SEG_PACK(6,1)  },
    { SEG_PACK(9,3),  SEG_PACK(9,2),  SEG_PACK(9,1),  SEG_PACK(9,0),  SEG_PACK(8,0),  SEG_PACK(8,2),  SEG_PACK(8,1)  },
    { SEG_PACK(11,3), SEG_PACK(11,2), SEG_PACK(11,1), SEG_PACK(11,0), SEG_PACK(10,0), SEG_PACK(10,2), SEG_PACK(10,1) },
    { SEG_PACK(13,3), SEG_PACK(13,2), SEG_PACK(13,1), SEG_PACK(13,0), SEG_PACK(12,0), SEG_PACK(12,2), SEG_PACK(12,1) }
};


// ============================================================
// Numeric digit masks
// ============================================================
// bit0=A bit1=B bit2=C bit3=D bit4=E bit5=F bit6=G

constexpr uint8_t DIGIT_MASKS[10] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

constexpr uint8_t DIGIT_BLANK = 0b00000000;
constexpr uint8_t DIGIT_MINUS = 0b01000000;