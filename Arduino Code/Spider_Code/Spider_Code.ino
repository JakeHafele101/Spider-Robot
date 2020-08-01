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
#define SERVO_DELAY 100 //Delay in milliseconds
#define WAVE_DELAY 250
#define PUSHUP_DELAY 250
#define BOUNCE_DELAY 250

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[NUM_LEG][SERVO_PER_LEG] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}};

const int J1Parallel[NUM_LEG] = {135, 41, 40, 125};
const int J1Forward[NUM_LEG] = {40, 10, 140, 170};
const int J1Backward[NUM_LEG] = {180, 130, 0, 30};

const int J2Right[NUM_LEG] = {44, 140, 135, 50};
const int J2Parallel[NUM_LEG] = {130, 50, 50, 135};
const int J2Inside[NUM_LEG] = {10, 180, 180, 20};

const int forwardOrder[NUM_LEG] = {1, 3, 0, 2};

RF24 radio(9, 10); //CE, CSN
const byte address[6] = "00001"; //Acts as key between receivers

int currentButton;

void setup() {

  radio.begin(); //Wireless receiver setup
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  Serial.begin(9600);
}

void loop() {

  if(radio.available()){
    radio.read(&currentButton, sizeof(currentButton));
    Serial.println(currentButton);
  }
  switch(currentButton){
    case 1:
      moveForward();
      break;
    case 2:
      moveBackward();
      break;
    case 3:
      turnRight();
      break;
    case 4:
      turnLeft();
      break;
    case 5:
      waveArm();
      break;
    case 6:
      pushUp();
      break;
    case 7:
      bounce();
      break;
    case 8:
      setNormal();
      break;
  }
}

void setRightAngle(){ //Sets every servo to 90 degrees so servos can be screwed in. Not used for final program
  for(int i = 0; i < NUM_LEG; i++){
    for(int j = 0; j < SERVO_PER_LEG; j++){
      setAngle(servo[i][j], 90);
    }
  }
}

void setNormal(){
  for(int i = 0; i < NUM_LEG; i++){ //Sets joint 1 parts to 90 degrees
    setAngle(servo[i][0], 90);
  }
  setAngle(servo[0][1], 90 - NORMAL_OFFSET);
  setAngle(servo[1][1], 90 + NORMAL_OFFSET);
  setAngle(servo[2][1], 90 + NORMAL_OFFSET);
  setAngle(servo[3][1], 90 - NORMAL_OFFSET);
  delay(SERVO_DELAY);
}

void moveForward(){ //Each leg takes one step forward
  setNormal();
  
  setJ2Inside(3);
  setJ1Parallel(3);
  delay(SERVO_DELAY);
  setJ2Right(3);

  setJ2Inside(2);
  setJ190(2);
  delay(SERVO_DELAY);
  setJ2Right(2);
  
  setJ2Inside(1);
  setJ2Inside(2);
  setJ1Parallel(1);
  setJ190(2);

  setJ190(3);
  setJ1Parallel(0);
  delay(SERVO_DELAY);

  setJ2Right(1);
  setJ2Right(2);
  delay(SERVO_DELAY);

  setJ2Inside(0);
  setJ2Inside(3);
  setJ1Parallel(3);
  setJ190(0);

  setJ190(1);
  setJ1Parallel(2);
  delay(SERVO_DELAY);

  setJ2Right(0);
  setJ2Right(3);
  delay(SERVO_DELAY);
}

void moveBackward(){ //Each leg takes one step backward
  setNormal();
  
  setJ2Inside(0);
  setJ1Parallel(0);
  delay(SERVO_DELAY);
  setJ2Right(0);

  setJ2Inside(1);
  setJ190(1);
  delay(SERVO_DELAY);
  setJ2Right(1);
  
  setJ2Inside(2);
  setJ2Inside(1);
  setJ1Parallel(2);
  setJ190(1);

  setJ190(0);
  setJ1Parallel(3);
  delay(SERVO_DELAY);

  setJ2Right(1);
  setJ2Right(2);
  delay(SERVO_DELAY);

  setJ2Inside(0);
  setJ2Inside(3);
  setJ1Parallel(0);
  setJ190(3);

  setJ190(2);
  setJ1Parallel(1);
  delay(SERVO_DELAY);

  setJ2Right(0);
  setJ2Right(3);
  delay(SERVO_DELAY);
}

void turnRight(){ //Each leg takes one step to the right
  setNormal();
  
  setJ2Inside(0);
  setJ2Inside(3);
  delay(SERVO_DELAY);

  setJ1Backward(1);
  setJ1Forward(2);
  delay(SERVO_DELAY);

  setJ2Right(0);
  setJ2Right(3);
  setJ2Inside(1);
  setJ2Inside(2);
  setJ190(1);
  setJ190(2);
  delay(SERVO_DELAY);

  setJ1Forward(3);
  setJ1Backward(0);
  delay(SERVO_DELAY);

  setJ290(1);
  setJ290(2);
}

void turnLeft(){ //Each leg takes one step to the left
  setNormal();
  
  setJ2Inside(0);
  setJ2Inside(3);
  delay(SERVO_DELAY);

  setJ1Forward(1);
  setJ1Backward(2);
  delay(SERVO_DELAY);

  setJ2Right(0);
  setJ2Right(3);
  setJ2Inside(1);
  setJ2Inside(2);
  setJ190(1);
  setJ190(2);
  delay(SERVO_DELAY);

  setJ1Backward(3);
  setJ1Forward(0);
  delay(SERVO_DELAY);

  setJ290(1);
  setJ290(2);
}

void waveArm(){ //Waves front right arm
  setJ2Right(1);
  setJ2Right(2);
  setJ2Right(3);
  setJ2Parallel(0);
  setJ1Parallel(0);
  delay(WAVE_DELAY);
  setAngle(1, 170);
  setJ1Forward(0);
  delay(WAVE_DELAY);
}

void pushUp(){
  setJ1Parallel(1);
  setJ1Parallel(3);
  setJ1Forward(0);
  setJ1Forward(2);
  for(int i = 0; i < NUM_LEG; i++){
    setJ2Right(i);
  }
  delay(PUSHUP_DELAY);
  setJ290(0);
  setJ290(2);
  delay(PUSHUP_DELAY);
}

void bounce(){
  setNormal();
  for(int i = 0; i < NUM_LEG; i++){
    setJ290(i);
  }
  delay(BOUNCE_DELAY);
}

int pulseWidth(int angle){ //Used to make servo driver angles set easier
  int pulseWide, analogValue;
  pulseWide = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  analogValue = int(float(pulseWide) / 1000000 * SERVO_FREQ * 4096);
  return analogValue;
}

void setAngle(int servo, int angle){
  pwm.setPWM(servo, 0, pulseWidth(angle));
}

void setJ190(int legNum){
  setAngle(servo[legNum][0], 90);
}

void setJ1Parallel(int legNum){
  setAngle(servo[legNum][0], J1Parallel[legNum]);
}

void setJ1Forward(int legNum){
  setAngle(servo[legNum][0], J1Forward[legNum]);
}

void setJ1Backward(int legNum){
  setAngle(servo[legNum][0], J1Backward[legNum]);
}

void setJ290(int legNum){
  setAngle(servo[legNum][1], 90);
}

void setJ2Right(int legNum){
  setAngle(servo[legNum][1], J2Right[legNum]);
}

void setJ2Parallel(int legNum){
  setAngle(servo[legNum][1], J2Parallel[legNum]);
}

void setJ2Inside(int legNum){
  setAngle(servo[legNum][1], J2Inside[legNum]);
}
