#include "ht1621.h"
#include <string.h>

Ht1621::Ht1621(uint8_t pinCs, uint8_t pinWr, uint8_t pinData)
    : cs_(pinCs), wr_(pinWr), data_(pinData)
{
    clear();
}

void Ht1621::begin()
{
    pinMode(cs_, OUTPUT);
    pinMode(wr_, OUTPUT);
    pinMode(data_, OUTPUT);

    digitalWrite(cs_, HIGH);
    digitalWrite(wr_, HIGH);
    digitalWrite(data_, LOW);

    delay(20);

    sendCommand(0x01); // SYS EN
    sendCommand(0x18); // RC OSC ON
    sendCommand(0x29); // 1/3 bias, 4 commons
    sendCommand(0x03); // LCD ON

    clear();
    flush();
}

void Ht1621::clear()
{
    memset(ram_, 0, sizeof(ram_));
}

void Ht1621::setSeg(SegId seg, bool on)
{
    const uint8_t addr = SEG_ADDR(seg);
    const uint8_t bit  = SEG_BIT(seg);
    const uint8_t mask = static_cast<uint8_t>(1u << bit);

    if (on) {
        ram_[addr] |= mask;
    } else {
        ram_[addr] &= static_cast<uint8_t>(~mask);
    }
}

void Ht1621::setDigitMask(const Digit7& d, uint8_t mask)
{
    setSeg(d.A, (mask & (1u << 0)) != 0);
    setSeg(d.B, (mask & (1u << 1)) != 0);
    setSeg(d.C, (mask & (1u << 2)) != 0);
    setSeg(d.D, (mask & (1u << 3)) != 0);
    setSeg(d.E, (mask & (1u << 4)) != 0);
    setSeg(d.F, (mask & (1u << 5)) != 0);
    setSeg(d.G, (mask & (1u << 6)) != 0);
}

void Ht1621::setDigitValue(uint8_t digitIndex, uint8_t value)
{
    if (digitIndex >= 15) return;

    if (value > 9) {
        setDigitMask(DIGITS[digitIndex], DIGIT_BLANK);
        return;
    }

    setDigitMask(DIGITS[digitIndex], DIGIT_MASKS[value]);
}

void Ht1621::setDigitBlank(uint8_t digitIndex)
{
    if (digitIndex >= 15) return;
    setDigitMask(DIGITS[digitIndex], DIGIT_BLANK);
}

void Ht1621::setDigitMinus(uint8_t digitIndex)
{
    if (digitIndex >= 15) return;
    setDigitMask(DIGITS[digitIndex], DIGIT_MINUS);
}

void Ht1621::flush()
{
    digitalWrite(cs_, LOW);

    sendBits(0b101, 3);
    sendBits(0, 6); // start address 0

    for (int i = 0; i < 32; ++i) {
        sendBits(ram_[i] & 0x0F, 4);
    }

    digitalWrite(cs_, HIGH);
    delayMicroseconds(20);
}

void Ht1621::wrPulse()
{
    digitalWrite(wr_, LOW);
    delayMicroseconds(5);
    digitalWrite(wr_, HIGH);
    delayMicroseconds(5);
}

void Ht1621::sendBits(uint16_t value, int count)
{
    for (int i = count - 1; i >= 0; --i) {
        digitalWrite(data_, (value >> i) & 0x01);
        delayMicroseconds(1);
        wrPulse();
    }
}

void Ht1621::sendCommand(uint8_t cmd)
{
    digitalWrite(cs_, LOW);
    sendBits(0b100, 3);
    sendBits(cmd, 8);
    sendBits(0, 1);
    digitalWrite(cs_, HIGH);
    delayMicroseconds(20);
}