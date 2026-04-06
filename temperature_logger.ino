#include <LiquidCrystal.h>
#include <EEPROM.h>

// For 8-bit mode: RS, EN, D0, D1, D2, D3, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 0, 1, 2, 3, 4, 5, 6, 7);

// Other pins (adjusted because D2, D3 are now used by LCD)
#define TMP36_PIN A0
#define BUTTON_PIN 8    // Changed from D2 to D8
#define BUZZER_PIN 9    // Changed from D3 to D9
#define TEMP_LIMIT 30.0

void setup() {
  // Initialize 8-bit LCD (16 chars, 2 lines)
  lcd.begin(16, 2);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initialize EEPROM
  if (EEPROM.read(0) == 0xFF) EEPROM.write(0, 100); // Min
  if (EEPROM.read(1) == 0xFF) EEPROM.write(1, 0);   // Max
  
  lcd.print("8-bit Mode Ready");
  delay(1000);
}

void loop() {
  // Read temperature
  int adc = analogRead(TMP36_PIN);
  float voltage = adc * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;
  
  // Check button
  if (digitalRead(BUTTON_PIN) == LOW) {
    EEPROM.write(0, (int)tempC);
    EEPROM.write(1, (int)tempC);
    delay(500);
  }
  
  // Update Min/Max
  int minTemp = EEPROM.read(0);
  int maxTemp = EEPROM.read(1);
  
  if (tempC < minTemp) EEPROM.write(0, (int)tempC);
  if (tempC > maxTemp) EEPROM.write(1, (int)tempC);
  
  // Buzzer control
  digitalWrite(BUZZER_PIN, tempC > TEMP_LIMIT ? HIGH : LOW);
  
  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Min:");
  lcd.print(minTemp);
  lcd.print(" Max:");
  lcd.print(maxTemp);
  delay(1000);
}
