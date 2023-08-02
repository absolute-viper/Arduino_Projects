void setup()
{
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(1,OUTPUT);

               
}


void loop(){
digitalWrite(16,LOW);
analogWrite(1,LOW);
digitalWrite(5,LOW);

digitalWrite(4,HIGH);
digitalWrite(0,HIGH);
digitalWrite(2,HIGH);

digitalWrite(14,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);

digitalWrite(15,HIGH);
digitalWrite(3,HIGH);
digitalWrite(10,HIGH);

}
