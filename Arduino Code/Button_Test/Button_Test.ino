
#define BUTTON_NUM 8

const int buttonDigital[BUTTON_NUM] = {3, 4, 5, 6, 7, 8, 9, 10};
int buttonState[8];

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < BUTTON_NUM; i++){
    pinMode(buttonDigital[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < BUTTON_NUM; i++){
    buttonState[i] = digitalRead(buttonDigital[i]);
    Serial.print(buttonState[i]);
    Serial.print("\t");
  }
  Serial.println();
}
