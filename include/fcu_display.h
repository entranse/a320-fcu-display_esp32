#pragma once
#include "ht1621.h"

class FcuDisplay
{
public:
    explicit FcuDisplay(Ht1621& lcd);

    void updateFromMobiflight(
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
        bool lvlChManaged);

private:
    Ht1621& lcd_;

    void clearSpeedPoints();
    void clearAltitudeSign();
    void setAltitudeMinus();
    void setAltitudePlus();
    void setDashDigits(uint8_t firstDigit, uint8_t count);
    void writeRightAlignedUnsigned(uint8_t firstDigit, uint8_t count, int value);
    void writeMachHundredths(uint8_t firstDigit, int mach100);

    void renderSpeedWindow(int value, bool machMode, bool dashes, bool managed);
    void renderHeadingWindow(int value, bool trkFpaMode, bool dashes, bool managed);
    void renderAltitudeWindow(int value, bool lvlChManaged);
    void renderVsFpaWindow(int value, bool trkFpaMode, bool dashes);
};