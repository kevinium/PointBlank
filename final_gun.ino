/*
 * Final Gun
 * No edits allowed
 */
int trigPin = 11;    // Trigger
int echoPin = 12;   // Echo
int button=2;
int bullet=6;
int warn = 4;
int ir = 6;
long duration, cm, inches;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7,OUTPUT);
  pinMode(ir,OUTPUT);
  pinMode(button,INPUT);
  pinMode(warn, OUTPUT);
}
 
void loop() 
{
  digitalWrite(ir, HIGH);
  if(bullet > 0)
  {
    if(digitalRead(2)==HIGH)
   {
      bullet--;
      digitalWrite(ir, LOW);
      delay(250);
      digitalWrite(ir,HIGH);
      Serial.print("shot");
    }
  }
  if(bullet<=0)
  {
    digitalWrite(warn, HIGH);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
 
    duration = pulseIn(echoPin, HIGH);
 
 
    cm = (duration/2) / 29.1;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    Serial.print("Time to Reload");
    if(cm<=20)
      {
        bullet=6;
        Serial.print("ok");
      }
  }
  else
  {
    digitalWrite(warn, LOW);
  }
  delay(250);
}
