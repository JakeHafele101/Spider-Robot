#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BUTTON_DIGITAL 3

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001"; //Acts as key between receivers


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(BUTTON_DIGITAL, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(BUTTON_DIGITAL);
  Serial.println(buttonState);

  radio.write(&buttonState, sizeof(buttonState));
}
