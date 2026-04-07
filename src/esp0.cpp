#include "iikit.h" 

void blinkLEDFunc(uint8_t pin) {
  digitalWrite(pin, !digitalRead(pin));
}

//Função que le os valores dos POT e das Entradas 4 a 20 mA e plota no display
void managerInputFunc(void) {
    const uint16_t vlPOT1 = IIKit.analogReadPot1();
    const uint16_t vlPOT2 = IIKit.analogReadPot2();
    IIKit.disp.setText(2, ("P1:" + String(vlPOT1)).c_str());
    IIKit.disp.setText(3, ("P2:" + String(vlPOT2)).c_str());    
    IIKit.WSerial.plot("vlPOT1", vlPOT1);
    IIKit.WSerial.plot("vlPOT2", vlPOT2);
}

void setup(){
  IIKit.setup();
  pinMode(def_pin_D1, OUTPUT);
}

#define TIME_DELAY_BLINK_MS 500
uint32_t previousTimeBlinkMS = 0;

#define TIME_DELAY_PRINT_MS 100
uint32_t previousTimePrintMS = 0;

void loop()
{
  IIKit.loop();
  uint32_t currentMilis = millis();
  if ((currentMilis - previousTimeBlinkMS) >= TIME_DELAY_BLINK_MS)
  {
    previousTimeBlinkMS = currentMilis;
    blinkLEDFunc(def_pin_D1);
  }
  if ((currentMilis - previousTimePrintMS) >= TIME_DELAY_PRINT_MS)
  {
    previousTimePrintMS = currentMilis;
    managerInputFunc();
  }  
}