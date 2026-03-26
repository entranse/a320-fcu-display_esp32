# A320 FCU LCD Display Test Driver

This project provides a simple driver to test a custom **A320 FCU LCD display** using an ESP32.

## Hardware

- **Target board:** ESP32  
- **Tested on:** ESP32-WROOM-32  

---

## ⚠️ Important Notes

- **Do NOT apply more than 3.3V to any ESP32 GPIO pin.**
- The LCD requires a **5V supply for VCC**, but this **must not be fed back into ESP32 pins**.

---

## Wiring

| LCD Pin | ESP32 Connection |
|--------|------------------|
| VCC    | 5V *(LCD only)*  |
| GND    | GND              |
| WR     | GPIO 18          |
| DAT    | GPIO 23          |
| CS     | GPIO 5           |
| LED+   | 3.3–5V           |
| LED-   | GND              |

---

## Pin Configuration

Pins can be adjusted in `main.cpp`:

```cpp
PIN_CS   = 5;
PIN_WR   = 18;
PIN_DATA = 23;
