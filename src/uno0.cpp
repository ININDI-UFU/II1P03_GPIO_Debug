#include <Arduino.h>
#define def_pin_D1 03
#define pinANALOG A5   

void printSerial(const uint32_t &currentMilis) {
  Serial.print(">graf:");
  Serial.print(currentMilis);
  Serial.print(":");
  Serial.print(analogRead(pinANALOG));
  Serial.println("|g");
}

void blinkLEDFunc(uint8_t pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void setup(){
  Serial.begin(9600);
  pinMode(def_pin_D1, OUTPUT);
}

#define TIME_DELAY_BLINK_MS 500
uint32_t previousTimeBlinkMS = 0;

#define TIME_DELAY_PRINT_MS 100
uint32_t previousTimePrintMS = 0;

void loop()
{
  uint32_t currentMilis = millis();
  if ((currentMilis - previousTimeBlinkMS) >= TIME_DELAY_BLINK_MS)
  {
    previousTimeBlinkMS = currentMilis;
    blinkLEDFunc(def_pin_D1);
  }
  if ((currentMilis - previousTimePrintMS) >= TIME_DELAY_PRINT_MS)
  {
    previousTimePrintMS = currentMilis;
    printSerial(currentMilis);
  }  
}