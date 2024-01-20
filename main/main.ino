#include "LedControl.h"
#include "BluetoothSerial.h"

#define P_DISPLAY_DIN 16
#define P_DISPLAY_CLK 17
#define P_DISPLAY_CS 18

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
LedControl lc = LedControl(P_DISPLAY_DIN,P_DISPLAY_CLK,P_DISPLAY_CS,1);
byte displayBuffer[8]={0,0,0,0,0,0,0,0};


void setup() {
 Serial.begin(115200);
  SerialBT.begin("PotolCore"); //Bluetooth device name
 Serial.println("The device started, now you can pair it with bluetooth!");

    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,2);
  /* and clear the display */
  lc.clearDisplay(0);


}

void loop() {

  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());
  // }
  if (SerialBT.available()) {
   blinkLed();
    uint8_t a = SerialBT.read();

    Serial.println("Received #" + String(a) +"#");
  

    // SerialBT.write(a+1);
  }

  // for(int i=0; i<8; i++){
  //   for(int j=0; j<8; j++){
  //     setCoOrdinates(i,j);
  //     flashDisplayBuffer();
  //     delay(200);
  //   }
  // }

  delay(10);

}

void setCoOrdinates(uint8_t x, uint8_t y){

  for(int i=0; i<8; i++){
    if(i == y)
      displayBuffer[y] = B00000001 << x;
    else
      displayBuffer[i] = 0;
  }
  

}

void flashDisplayBuffer(){
  for(int i=0; i<8; i++){
//    lc.setRow(0, i, displayBuffer[i]);
  }
}

void blinkLed(){
  lc.setLed(0, 0, 0, 1);
  delay(100);
  lc.setLed(0, 0, 0, 0);
}
