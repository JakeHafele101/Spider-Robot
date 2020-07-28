
#define LED_DIGITAL_1 2
#define LED_DIGITAL_2 3


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_DIGITAL_1, OUTPUT);
  pinMode(LED_DIGITAL_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_DIGITAL_1, HIGH);
  digitalWrite(LED_DIGITAL_2, HIGH);
}
