#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BUTTON_NUM 8

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001"; //Acts as key between receivers

const int buttonDigital[BUTTON_NUM] = {A2, A1, A0, 6, 5, 4, 3, 2};
int buttonState[BUTTON_NUM];
boolean isButtonActive[BUTTON_NUM];

void setup() {
  for(int i = 0; i < BUTTON_NUM; i++){ //Button pin setup
    pinMode(buttonDigital[i], INPUT);
    isButtonActive[i] = false; //Sets buttons so they all havent been recognized as pressed yet
  }
  
  radio.begin(); //Wireless receiver setup
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(9600); //Serial monitor setup
}

void loop() {
  
  for(int i = 0; i < BUTTON_NUM; i++){ //Checks data of button pins
    buttonState[i] = digitalRead(buttonDigital[i]);
//    Serial.print(buttonState[i]);
//    Serial.print("\t");
  }
//  Serial.println();

  for(int i = 0; i < BUTTON_NUM; i++){ //Condition checks for buttons being held/pressed
    if(buttonState[i] && !isButtonActive[i]){ //Checks if buttonState is 1 and isButtonActive is false
      isButtonActive[i] = true;
      int buttonSent = i + 1;
      Serial.println(buttonSent);
      radio.write(&buttonSent, sizeof(buttonSent));
    }
    else if(!buttonState[i] && isButtonActive[i]){ //Checks if buttonState is 0 and isButtonActive is true
      isButtonActive[i] = false;
    }
  }
}
