#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#define OLED_ADDR 0x3c
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RESET 16

SSD1306Wire display(OLED_ADDR, OLED_SDA, OLED_SCL);

int counter = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, LOW);
  delay(50);
  digitalWrite(OLED_RESET, HIGH);
  Wire.begin(OLED_SDA, OLED_SCL);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

String inputString = "";
bool stringComplete = false; // whether the string is complete

void loop()
{
  if (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }

  if (stringComplete)
  {
    Serial.println(inputString);

    inputString = "";
    stringComplete = false;
  }

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "Hello world");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 24, "serial...");
  display.display();
  delay(2000);
}