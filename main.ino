//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define OPIN_0 16
#define OPIN_1 17
#define OPIN_2 18
#define OPIN_3 19

BluetoothSerial SerialBT;



void setup() {
 Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
 // Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(OPIN_0, OUTPUT);
  pinMode(OPIN_1, OUTPUT);
  pinMode(OPIN_2, OUTPUT);
  pinMode(OPIN_3, OUTPUT);

}

void loop() {




  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());
  // }
  if (SerialBT.available()) {

    uint8_t a = SerialBT.read();

    Serial.println("Received #" + String(a) +"#");
    // int a = SerialBT.read();

    // SerialBT.write(a+1);
  }

  uint8_t number = B00000001;

  ledJalao(number);
  delay(1000);

  ledJalao(number << 1);
  delay(1000);
  ledJalao(number << 2);
  delay(1000);
  ledJalao(number << 3);
  delay(1000);





}

void ledJalao(uint8_t number){
  if (number & B00000001)
    digitalWrite(OPIN_0, HIGH);
  else
    digitalWrite(OPIN_0, LOW);

  if ((number & B00000010) >> 1)
    digitalWrite(OPIN_1, HIGH);
  else
    digitalWrite(OPIN_1, LOW);

  if ((number & B00000100) >> 2)
    digitalWrite(OPIN_2, HIGH);
  else
    digitalWrite(OPIN_2, LOW);

  if ((number & B00001000) >> 3)
    digitalWrite(OPIN_3, HIGH);
  else
    digitalWrite(OPIN_3, LOW);

}