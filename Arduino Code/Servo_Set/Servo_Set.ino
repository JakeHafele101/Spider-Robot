#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2400 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define SERVO_PER_LEG 3
#define NUM_LEG 4


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[4][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}};


void setup() {

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {
  
//  for(int i = 0; i < NUM_LEG; i++){
//    for(int j = 0; j < SERVO_PER_LEG; j++){
//      pwm.setPWM(servo[i][j], 0, pulseWidth(90));
//    }
//  }

//  pwm.setPWM(0, 0, pulseWidth(90));
//  pwm.setPWM(2, 0, pulseWidth(0));
//  pwm.setPWM(4, 0, pulseWidth(90));
//  pwm.setPWM(6, 0, pulseWidth(180));

  pwm.setPWM(0, 0, pulseWidth(180));
  pwm.setPWM(2, 0, pulseWidth(90));
  pwm.setPWM(4, 0, pulseWidth(20));
  pwm.setPWM(6, 0, pulseWidth(90));

//  pwm.setPWM(0, 0, pulseWidth(90));
//  pwm.setPWM(2, 0, pulseWidth(90));
//  pwm.setPWM(4, 0, pulseWidth(90));
//  pwm.setPWM(6, 0, pulseWidth(90));

  

  pwm.setPWM(1, 0, pulseWidth(45));
  pwm.setPWM(3, 0, pulseWidth(135));
  pwm.setPWM(5, 0, pulseWidth(135));
  pwm.setPWM(7, 0, pulseWidth(45));

//  pwm.setPWM(1, 0, pulseWidth(90));
//  pwm.setPWM(3, 0, pulseWidth(90));
//  pwm.setPWM(5, 0, pulseWidth(90));
//  pwm.setPWM(7, 0, pulseWidth(90));


  //pwm.setPWM(0, 0, pulseWidth(90));
  //pwm.setPWM(1, 0, pulseWidth(135));
  //pwm.setPWM(2, 0, pulseWidth(45));

  delay(100);
  
  
}

int pulseWidth(int angle){
  int pulseWide, analogValue;
  pulseWide = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  analogValue = int(float(pulseWide) / 1000000 * SERVO_FREQ * 4096);
  return analogValue;
}
