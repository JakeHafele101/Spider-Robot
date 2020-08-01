#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); //CE, CSN

const byte address[6] = "00001"; //Acts as key between receivers

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()){
    int buttonState = 0;
    radio.read(&buttonState, sizeof(buttonState));
    if(buttonState != 0){
      Serial.println(buttonState);
    }
  }
}
