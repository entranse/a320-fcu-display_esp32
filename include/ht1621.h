#pragma once
#include <Arduino.h>
#include "lcd_segments.h"

class Ht1621
{
public:
    Ht1621(uint8_t pinCs, uint8_t pinWr, uint8_t pinData);

    void begin();
    void clear();
    void flush();

    void setSeg(SegId seg, bool on);
    void setDigitMask(const Digit7& d, uint8_t mask);
    void setDigitValue(uint8_t digitIndex, uint8_t value);
    void setDigitBlank(uint8_t digitIndex);
    void setDigitMinus(uint8_t digitIndex);

private:
    uint8_t cs_;
    uint8_t wr_;
    uint8_t data_;
    uint8_t ram_[32];

    void wrPulse();
    void sendBits(uint16_t value, int count);
    void sendCommand(uint8_t cmd);
};