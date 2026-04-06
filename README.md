# EEPROM-Based Temperature Logger with LCD Display

![Platform](https://img.shields.io/badge/platform-Tinkercad-blue)
![Language](https://img.shields.io/badge/language-Embedded%20C-green)
![MCU](https://img.shields.io/badge/MCU-ATmega328P-red)

## 📌 Overview

This project demonstrates an embedded system that measures ambient temperature using a **TMP36 sensor**, processes data using the inbuilt ADC of **ATmega328P**, and displays the temperature on a **16×2 LCD**. Temperature data is stored in **EEPROM** to retain minimum and maximum values even after power loss.

## 🎯 Objectives

- Interface ATmega328P with TMP36 temperature sensor
- Read temperature using inbuilt ADC every second
- Display temperature data on 16×2 LCD
- Implement logic using Embedded C (register-level programming)
- Simulate complete system using Tinkercad

## 🧠 Working Principle

The TMP36 sensor generates an analog voltage proportional to temperature. The ATmega328P's ADC reads this voltage every second and converts it to degrees Celsius. The current temperature is displayed on the LCD while the system compares it with stored min/max values in EEPROM, updating them when necessary.

## 📋 Components (Simulated in Tinkercad)

| Component | Description |
|-----------|-------------|
| ATmega328P | Simulated microcontroller |
| TMP36 | Temperature sensor |
| LCD 16×2 | Display module |
| EEPROM | Internal EEPROM |
| Power Supply | 5V supply |
| Buzzer | Alerts when temperature > 30°C |
| Push Button | Reset min/max values |

## 🔌 Pin Connections

| Component | Pin |
|-----------|-----|
| LCD RS | D12 |
| LCD EN | D11 |
| LCD D0-D7 | D0-D7 |
| TMP36 | A0 |
| Button | D8 |
| Buzzer | D9 |

## 💻 Code Example

```c
// Read temperature from TMP36
int adc = analogRead(TMP36_PIN);
float voltage = adc * (5.0 / 1023.0);
float tempC = (voltage - 0.5) * 100.0;

// Update EEPROM min/max
if (tempC < minTemp) EEPROM.write(0, (int)tempC);
if (tempC > maxTemp) EEPROM.write(1, (int)tempC);
