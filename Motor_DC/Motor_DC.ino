int ENA = D6;
int IN1 = D4;
int IN2 = D3;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  setDirection();
  delay(1000);
  changeSpeed();
  delay(1000);
}

void setDirection() {
  analogWrite(ENA, 255);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(5000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(5000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void changeSpeed() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  for (int i = 100; i < 256; i++) {
    analogWrite(ENA, i);
    delay(20);
  }
  
  for (int i = 255; i >= 100; --i) {
    analogWrite(ENA, i);
    delay(20);
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
