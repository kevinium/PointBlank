/*
No edits allowed in this particular code
*/
import processing.serial.*;//includes the serial object library
Serial mySerial;//makes an object from serial library
String myString=null ;//Variable to collect serial data
int nl= 10; //ASCII Code 
int sVal; //float for storing converted ASCII serial data
int rVal, counter=0;
int screen=0;
void setup()
{
    size(1280,640); 
    String myPort = Serial.list() [2];
    mySerial=new Serial(this, myPort, 9600);
}
void draw()
{
    if(screen==0)
    {
        background(250,0,0);
        fill(0, 102, 255);
        rect(20, 20, 1240, 600, 200);
        fill(0);
        textSize(48);
        text("Infrared Shooting Game", 380, 60);
        fill(0, 230, 0);
        rect(240, 200, 800, 100, 500);
        fill(0);
        text("Single Player", 480, 270);
        fill(0, 230, 0);
        rect(240, 380, 800, 100, 500);
        fill(0);
        text("Multiplayer", 480, 450);
        /*fill(0,230,0);     
        rect(950, 540, 150, 50, 500);
        textSize(20);
        fill(0);
        text("New Game", 980, 570);*/
        if(mousePressed && mouseX<1040 && mouseX>240 && mouseY<300 && mouseY>200)
        { 
          screen=3;
        }
        else if(mousePressed && mouseX<1040 && mouseX>240 && mouseY<480 && mouseY>380)
        {
          mySerial.write(1);  
          screen=2;
          counter=0;
        }
    }
    else if(screen==3)
    {
          size(1280,640);  
          background(250,0,0);
          fill(0, 102, 255);
          rect(20, 20, 1240, 600, 200);
          fill(0);
          textSize(48);
          text("SINGLEPLAYER", 500, 60);
          fill(0, 230, 0);
          rect(240, 120, 800, 100, 500);
          fill(0);
          textSize(44);
          text("NOOB MODE", 500, 200);
          fill(0, 230, 0);
          rect(240, 320, 800, 100, 500);
          fill(0);
          textSize(44);
          text("PRO MODE", 520, 400);
          if(mousePressed && mouseX<1040 && mouseX>240 && mouseY<220 && mouseY>120)
          {
          mySerial.write(0);  
          screen=1;
          counter=0;
          }
          if(mousePressed && mouseX<1040 && mouseX>240 && mouseY<320 && mouseY>220)
          {
          mySerial.write(2);  
          screen=1;
          counter=0;
          }
    }
    else if(screen==1)
    {
       while(mySerial.available()>0)
          {
           myString=mySerial.readStringUntil(nl);
        
          if (myString!=null)
          {
          size(1280,640);  
          background(250,0,0);
          fill(0, 102, 255);
          rect(20, 20, 1240, 600, 200);
          fill(0);
          textSize(48);
          text("SCOREBOARD", 500, 60);
          fill(0, 230, 0);
          rect(240, 120, 800, 400, 500);
          fill(0);
          textSize(44);
          text("SHOOTER'S SCORE", 460, 160);
          fill(0);
          textSize(200);
          text(myString, 520, 420);
          counter++;
          }
          }
          if(counter==12)
          {
           fill(0);
           textSize(44);
           text("Game Over", 530, 580);
         fill(0,230,0);     
          rect(950, 540, 150, 50, 500);
          textSize(20);
          fill(0);
          text("New Game", 980, 570);
          if(mousePressed && mouseX<1100 && mouseX>950 && mouseY<590 && mouseY>540)
          {
            screen=0;
          }
          }
        }
    else if(screen==2)
    { 
          while(mySerial.available()>0)
          {
            myString=mySerial.readStringUntil(nl);
            if (myString!=null)
            {
           size(1280,640);  
          background(250,0,0);
          fill(0, 102, 255);
          rect(20, 20, 1240, 600, 200);
          fill(0);
          textSize(48);
          text("SCOREBOARD", 500, 60);
          fill(0, 230, 0);
          rect(240, 120, 800, 400, 500);
          fill(0);
          textSize(44);
          text("SHOOTER'S SCORE", 460, 160);
          fill(0);
          textSize(200);
          text(myString, 520, 420);
          sVal=int(myString);
          counter++;
                 }
        }
        if(counter==12)
        {
        if(sVal>6)
        {
            textSize(30);
            fill(0);
            text("Shooter Wins", 540, 580);
        }
        if(sVal<6)
        {
            textSize(30);
            fill(0);
            text("Reciever Wins", 540, 580);
        }
        if(sVal==6)
        {
            textSize(30);
            fill(0);
            text("Draw", 620, 580);
        }
         fill(0,230,0);     
          rect(950, 540, 150, 50, 500);
          textSize(20);
          fill(0);
          text("New Game", 980, 570);
          if(mousePressed && mouseX<1100 && mouseX>950 && mouseY<590 && mouseY>540)
          {
            screen=0;
          }
        }
    }
 }
