#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define LED_DIGITAL_1 2
#define LED_DIGITAL_2 3

#define SERVO_PER_LEG 3
#define NUM_LEG 4

#define BUTTON_QUEUE_LENGTH 20

Servo servos[NUM_LEG][SERVO_PER_LEG];
const int servoDigital[4][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13}};

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001"; //Acts as key between receivers

int buttonQueue[BUTTON_QUEUE_LENGTH];

void setup() {
  
  pinMode(LED_DIGITAL_1, OUTPUT); //LED pin setup
  pinMode(LED_DIGITAL_2, OUTPUT);

  radio.begin(); //Wireless receiver setup
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  for(int i = 0; i < NUM_LEG; i++){ //Servo pin setup
    for(int j = 0; j < SERVO_PER_LEG; j++){
      servos[i][j].attach(servoDigital[i][j]);
    }
  }

  for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){ //Sets whole button queue array to 0 so no null errors
    buttonQueue[i] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(LED_DIGITAL_1, HIGH);
  digitalWrite(LED_DIGITAL_2, HIGH);

  if(radio.available()){
    int nextButton;
    radio.read(&nextButton, sizeof(nextButton));
    Serial.println(nextButton);
    addButtonQueue(nextButton);
  }

  setRightAngle();
}

void addButtonQueue(int nextButton){ //Adds button to end of queue array 
  for(int i = 0; i < BUTTON_QUEUE_LENGTH){
    if(buttonQueue[i] == 0){ //Checks if there is a queue slot at index i of buttonQueue array
      buttonQueue[i] = nextButton;
      return; //Returns so only one number added to array
    }
  }
}

void removeButtonQueue(){ //Removes the first button number from queue, ideally after the action is done
  for(int i = 0; i < BUTTON_QUEUE_LENGTH - 1; i++){
    buttonQueue[i] = buttonQueue[i + 1];
  }
  buttonQueue[BUTTON_QUEUE_LENGTH - 1] = 0;
}

void setRightAngle(){ //Sets every servo to 90 degrees so servos can be screwed in. Not used for final program
  for(int i = 0; i < NUM_LEG; i++){
    for(int j = 0; j < SERVO_PER_LEG; j++){
      servos[i][j].write(90);
    }
  }
}

void moveForward(){ //Each leg takes one step forward
  
}

void moveBackward(){ //Each leg takes one step backward
  
}

void moveRight(){ //Each leg takes one step to the right
  
}

void moveLeft(){ //Each leg takes one step to the left
  
}

void waveArm(){ //Waves front right arm
  
}

void action2(){
  
}

void action3(){
  
}

void action4(){
  
}
