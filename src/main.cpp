#include <Arduino.h>
#include "ht1621.h"
#include "fcu_display.h"

static constexpr uint8_t PIN_CS   = 5;
static constexpr uint8_t PIN_WR   = 18;
static constexpr uint8_t PIN_DATA = 23;

Ht1621 ht(PIN_CS, PIN_WR, PIN_DATA);
FcuDisplay fcu(ht);

void setup()
{
    Serial.begin(115200);
    ht.begin();
}

void loop()
{
    // Demo values
    fcu.updateFromMobiflight(
        78,     // SPD/MACH value: 78 => 0.78 in Mach mode
        123,    // HDG/TRK value
        38000,  // ALT value
        1200,  // VS/FPA value
        true,   // MACH mode
        false,  // TRK/FPA mode
        false,  // SPD/MACH dashes
        false,  // HDG/TRK dashes
        false,  // VS/FPA dashes
        true,   // SPD/MACH managed
        false,  // HDG/TRK managed
        false    // LVL/CH managed
    );

    delay(1000);
}