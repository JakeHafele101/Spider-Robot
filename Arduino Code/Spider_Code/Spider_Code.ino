#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2400 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define SERVO_PER_LEG 2
#define NUM_LEG 4

#define NORMAL_OFFSET 45

#define BUTTON_QUEUE_LENGTH 20
#define SERVO_DELAY 500 //Delay in milliseconds

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[NUM_LEG][SERVO_PER_LEG] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}};
const int servoOffset[NUM_LEG][SERVO_PER_LEG] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001"; //Acts as key between receivers

int buttonQueue[BUTTON_QUEUE_LENGTH];

void setup() {

  radio.begin(); //Wireless receiver setup
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){ //Sets whole button queue array to 0 so no null errors
    buttonQueue[i] = 0;
  }

  Serial.begin(9600);
}

void loop() {

  if(radio.available()){
    int nextButton;
    radio.read(&nextButton, sizeof(nextButton));
    Serial.println(nextButton);
    addButtonQueue(nextButton);
  }
  setNormal();
  switch(buttonQueue[0]){
    case 1:
      moveForward();
      break;
    case 2:
      moveBackward();
      break;
    case 3:
      moveRight();
      break;
    case 4:
      moveLeft();
      break;
    case 5:
      waveArm();
      break;
    case 6:
      action2();
      break;
    case 7:
      action3();
      break;
    case 8:
      action4();
      break;
  }
  moveForward();
  setNormal();
  removeButtonQueue();
}

void addButtonQueue(int nextButton){ //Adds button to end of queue array 
  for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
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
      pwm.setPWM(servo[i][j], 0, pulseWidth(90));
    }
  }
}

void setNormal(){
  for(int i = 0; i < NUM_LEG; i++){ //Sets joint 1 parts to 90 degrees
    pwm.setPWM(servo[i][0], 0, pulseWidth(90)); 
  }
  pwm.setPWM(servo[0][1], 0, pulseWidth(90 - NORMAL_OFFSET)); //Sets joint 2 parts to be perpendicular to joint 1
  pwm.setPWM(servo[1][1], 0, pulseWidth(90 + NORMAL_OFFSET));
  pwm.setPWM(servo[2][1], 0, pulseWidth(90 + NORMAL_OFFSET));
  pwm.setPWM(servo[3][1], 0, pulseWidth(90 - NORMAL_OFFSET));
  delay(SERVO_DELAY);
}

void moveForward(){ //Each leg takes one step forward
  pwm.setPWM(servo[1][0], 0, pulseWidth(20));
  pwm.setPWM(servo[3][0], 0, pulseWidth(160));
  delay(SERVO_DELAY);
  pwm.setPWM(servo[0][0], 0, pulseWidth(160));
  pwm.setPWM(servo[1][0], 0, pulseWidth(135));
  pwm.setPWM(servo[2][0], 0, pulseWidth(20));
  pwm.setPWM(servo[3][0], 0, pulseWidth(45));
  delay(SERVO_DELAY);
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

int pulseWidth(int angle){ //Used to make servo driver angles set easier
  int pulseWide, analogValue;
  pulseWide = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  analogValue = int(float(pulseWide) / 1000000 * SERVO_FREQ * 4096);
  return analogValue;
}
