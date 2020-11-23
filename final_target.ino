/*
 * Final target
 * No edits allowed
 */
#include <MPU6050.h>
#include<Wire.h>
MPU6050 mpu;
long randNumber;
int counter = 0;
int score = 0;
int flag;
int select = 0;
int x0, x1, x2, x3;//threshold for ifrec
int k0, k1, k2, k3;//input from ir
int k;//selecter
int pronoob;
unsigned long start, current, q;
void setup() {
  Serial.begin(9600);
  //Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
 
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  

  randomSeed(analogRead(0));
  //4 target LEDs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);


  //4 target IRs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT); 
}

void loop() {
  //select = 0;
  score = 0;
  k = Serial.read();
  
  current = millis();
  //threshold setup
  while(millis()-current < 100)
  {
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    x0 = analogRead(A0) + 30;
    x1 = analogRead(A1) + 30;
    x2 = analogRead(A2) + 30;
    x3 = analogRead(A3) + 30;
  }
  
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  
  if(k == 0)
  {
    //singlePlayerNoob
    pronoob = 1500;
  }
  if(k == 2)
  {
    //singlePlayerPro
    pronoob = 1000;
  }
  

  if(k == 1)
  {
    //Multiplayer
    counter = 0;
    while(counter < 12)
    {
      int bar = 0;
      randNumber = random(4) + 8;
      flag = 0;
      delay(1000);
      digitalWrite(randNumber, HIGH);
      start = millis();
      while(millis()-start < 1500)
      {
        
        Vector normGyro = mpu.readNormalizeGyro();
        if(normGyro.YAxis > 100 && bar == 0)
        {
          digitalWrite(randNumber, LOW);
          if(randNumber == 11)
          {
            randNumber = 8;
          }
          else
          {
            randNumber = randNumber + 1;
          }
          bar = 1;
          digitalWrite(randNumber, HIGH);
          k0 = analogRead(A0);
          k1 = analogRead(A1);
          k2 = analogRead(A2);
          k3 = analogRead(A3);
 
        }
         else if(normGyro.YAxis < -100 && bar == 0)
        {
          digitalWrite(randNumber, LOW);
          if(randNumber == 8)
          {
            randNumber = 11;
          }
          else
          {
            randNumber = randNumber - 1;
          }
          bar = 1;
          
          digitalWrite(randNumber, HIGH);
          k0 = analogRead(A0);
          k1 = analogRead(A1);
          k2 = analogRead(A2);
          k3 = analogRead(A3);
         }
         else 
         {
          k0 = analogRead(A0);
          k1 = analogRead(A1);
          k2 = analogRead(A2);
          k3 = analogRead(A3);
         }
        
  
        if(randNumber == 8)
        {
          if(k0 > x0 && k1 < x1 && k2 < x2 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k1 > x1 || k2 > x2 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 9)
        {
          if(k1 > x1 && k0 < x0 && k2 < x2 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k0 > x1 || k2 > x2 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 10)
        {
          if(k2 > x2 && k0 < x0 && k1 < x1 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k0 > x0 || k1 > x1 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 11)
        {
          if(k3 > x3 && k0 < x0 && k1 < x1 && k2 < x2)
          {
            flag = 1;
            break;
          }
          if(k0 > x0 || k1 > x1 || k2 > x2)
          {
            flag = 0;
            break;
          }
        }
      }
      if(flag == 1)
      {
        score++;
      }
      Serial.println(score);
      digitalWrite(randNumber, LOW);
      counter++;
    }
    if(score > 6)
    {
      Serial.println("SHOOTER WINS!");
    }
    else if(score < 6)
    {
      Serial.println("DEFENDER WINS!");
    }
    else
    {
      Serial.println("IT'S A DRAW!");
    }
  }
  if(k == 0 || k == 2) 
  {
    //SinglePlayer
    counter = 0;
    while(counter < 12)
    {
      randNumber = random(4) + 8;
      flag = 0;
      //Serial.println(randNumber);
      delay(1000);
      digitalWrite(randNumber, HIGH);
      start = millis();
      while((millis()-start )< pronoob)
      {
        k0 = analogRead(A0);
        k1 = analogRead(A1);
        k2 = analogRead(A2);
        k3 = analogRead(A3);
        if(randNumber == 8)
        {
          if(k0 > x0 && k1 < x1 && k2 < x2 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k1 > x1 || k2 > x2 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 9)
        {
          if(k1 > x1 && k0 < x0 && k2 < x2 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k0 > x0 || k2 > x2 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 10)
        {
          if(k2 > x2 && k0 < x0 && k1 < x1 && k3 < x3)
          {
            flag = 1;
            break;
          }
          if(k0 > x0 || k1 > x1 || k3 > x3)
          {
            flag = 0;
            break;
          }
        }
        if(randNumber == 11)
        {
          if(k3 > x3 && k0 < x0 && k2 < x2 && k1 < x1)
          {
            flag = 1;
            break;
          }
          if(k0 > x0 || k1 > x1 || k2 > x2)
          {
            flag = 0;
            break;
          }
        }
      }
      if(flag == 1)
      {
        score++;
      }
      Serial.println(score);
      digitalWrite(randNumber, LOW);
      counter++;
    }
  }
}
