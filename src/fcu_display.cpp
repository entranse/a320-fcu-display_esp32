#include "fcu_display.h"

FcuDisplay::FcuDisplay(Ht1621& lcd) : lcd_(lcd) {}

void FcuDisplay::updateFromMobiflight(
    int  spdMachValue,
    int  hdgTrkValue,
    int  altValue,
    int  vsFpaValue,
    bool machMode,
    bool trkFpaMode,
    bool spdMachDashes,
    bool hdgTrkDashes,
    bool vsFpaDashes,
    bool spdMachManaged,
    bool hdgTrkManaged,
    bool lvlChManaged)
{
    lcd_.clear();

    renderSpeedWindow(spdMachValue, machMode, spdMachDashes, spdMachManaged);
    renderHeadingWindow(hdgTrkValue, trkFpaMode, hdgTrkDashes, hdgTrkManaged);
    renderAltitudeWindow(altValue, lvlChManaged);
    renderVsFpaWindow(vsFpaValue, trkFpaMode, vsFpaDashes);

    lcd_.flush();
}

void FcuDisplay::clearSpeedPoints()
{
    lcd_.setSeg(SPD_POINT_1, false);
    lcd_.setSeg(SPD_POINT_2, false);
    lcd_.setSeg(SPD_POINT_3, false);
}

void FcuDisplay::clearAltitudeSign()
{
    lcd_.setSeg(ALT_PLUS_BAR, false);
    lcd_.setSeg(ALT_MINUS, false);
}

void FcuDisplay::setAltitudeMinus()
{
    lcd_.setSeg(ALT_PLUS_BAR, false);
    lcd_.setSeg(ALT_MINUS, true);
}

void FcuDisplay::setAltitudePlus()
{
    lcd_.setSeg(ALT_PLUS_BAR, true);
    lcd_.setSeg(ALT_MINUS, true);
}

void FcuDisplay::setDashDigits(uint8_t firstDigit, uint8_t count)
{
    for (uint8_t i = 0; i < count; ++i) {
        lcd_.setDigitMinus(firstDigit + i);
    }
}

void FcuDisplay::writeRightAlignedUnsigned(uint8_t firstDigit, uint8_t count, int value)
{
    for (uint8_t i = 0; i < count; ++i) {
        lcd_.setDigitBlank(firstDigit + i);
    }

    int v = value;
    for (int pos = firstDigit + count - 1; pos >= firstDigit; --pos) {
        lcd_.setDigitValue(pos, static_cast<uint8_t>(v % 10));
        v /= 10;
    }
}

void FcuDisplay::writeMachHundredths(uint8_t firstDigit, int mach100)
{
    mach100 = constrain(mach100, 10, 99);

    lcd_.setDigitValue(firstDigit + 0, 0);
    lcd_.setDigitValue(firstDigit + 1, static_cast<uint8_t>((mach100 / 10) % 10));
    lcd_.setDigitValue(firstDigit + 2, static_cast<uint8_t>(mach100 % 10));
}

void FcuDisplay::renderSpeedWindow(int value, bool machMode, bool dashes, bool managed)
{
    lcd_.setSeg(SPD_LABEL, !machMode);
    lcd_.setSeg(MACH_LABEL, machMode);
    lcd_.setSeg(SPD_MANAGED_DOT, managed);

    clearSpeedPoints();

    if (dashes) {
        setDashDigits(0, 3);
        return;
    }

    if (machMode) {
        // 10..99 => 0.10..0.99
        writeMachHundredths(0, value);

        // Decimal point after the leading zero
        lcd_.setSeg(SPD_POINT_2, true);
        return;
    }

    writeRightAlignedUnsigned(0, 3, constrain(value, 100, 399));
}

void FcuDisplay::renderHeadingWindow(int value, bool trkFpaMode, bool dashes, bool managed)
{
    lcd_.setSeg(HDG_LABEL, !trkFpaMode);
    lcd_.setSeg(TRK_LABEL, trkFpaMode);
    lcd_.setSeg(LAT_LABEL, false);
    lcd_.setSeg(HDG_TRK_MANAGED_DOT, managed);

    if (dashes) {
        setDashDigits(3, 3);
        return;
    }

    writeRightAlignedUnsigned(3, 3, constrain(value, 0, 359));
}

void FcuDisplay::renderAltitudeWindow(int value, bool lvlChManaged)
{
    lcd_.setSeg(ALT_LABEL_, true);
    lcd_.setSeg(LVLCH_LABEL, lvlChManaged);
    lcd_.setSeg(ALT_MANAGED_DOT, lvlChManaged);

    writeRightAlignedUnsigned(6, 5, constrain(value, 0, 99999));
}

void FcuDisplay::renderVsFpaWindow(int value, bool trkFpaMode, bool dashes)
{
    lcd_.setSeg(MODE_HDG_LABEL, !trkFpaMode);
    lcd_.setSeg(MODE_TRK_LABEL, trkFpaMode);
    lcd_.setSeg(MODE_VS_LABEL, !trkFpaMode);
    lcd_.setSeg(MODE_FPA_LABEL, trkFpaMode);

    lcd_.setSeg(ALT_VS_LABEL, !trkFpaMode);
    lcd_.setSeg(ALT_FPA_LABEL, trkFpaMode);

    lcd_.setSeg(ALT_CHANGE_POINT, false);
    clearAltitudeSign();

    if (dashes) {
        setDashDigits(11, 4);
        return;
    }

    const bool negative = value < 0;
    const int absVal = constrain(abs(value), 0, 9999);

    if (negative) {
        setAltitudeMinus();
    } else if (absVal > 0) {
        setAltitudePlus();
    }

    if (trkFpaMode) {
        lcd_.setSeg(ALT_CHANGE_POINT, true);
    }

    writeRightAlignedUnsigned(11, 4, absVal);
}