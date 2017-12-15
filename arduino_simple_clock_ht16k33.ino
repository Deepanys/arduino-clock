/* 
 *  This example displays simple arduino clock displayed in 7 segment using Ht16k33
 *  
 *  pin config:
 scl - On Arduino UNO thats Analog #5, on the Leonardo its Digital #3, on the Mega its digital #21
sda - On Arduino UNO thats Analog #4, on the Leonardo its Digital #2, on the Mega its digital #20
vcc - +5 V
Gnd - 0 V
A0 - A segment
A1 - B
A2 - C
A3 - D
.
.
.
.
A7 - Decimal point

c0 - cathode 1
c1 - cathode 2
c2 - colon cathode
c3 - cathode 3
c4 - cathode 4


arduino 
  pin 10 = push button for minute
  pin 11 = push button for hour (To increase hour & min you need to pull down the push button to ground )

created 12 Dec. 2017
  by Deepan

 *  
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();    // creating function for first Ht16k33 (0x70)


int h=12,m,s,bl=0;  
int flag,TIME; 
String clc;
const int hs=11; 
const int ms=10; 
int state1; 
int state2; 
void setup() 
  { 
      Serial.begin(9600);
      pinMode(hs, INPUT_PULLUP); 
      pinMode(ms, INPUT_PULLUP);
      Serial.println(" Seven Segment Display Test");
      matrix.begin(0x70);                               // creating first matrix
      matrix.setBrightness(15);                         // setting brightness for display (0 - 15)
      //matrix.blinkRate(1) ;                           // You can blink the entire display. 0 is no blinking. 1, 2 or 3 is for display blinking.
  } 
void loop() 
  { 

    s=s+1;            // second increment                                  
    clc="Time = ";    // storing time in string                             
    clc=clc+h;                                    
    clc=clc+":"+m;
    clc=clc+":"+s;                                     

    if(flag<12)                                   
    clc=clc+"AM";
    if(flag==12)
    clc=clc+"PM"; 
    if(flag>12)
    clc=clc+"PM";

    Serial.println(clc); // printing time in serial
 
 
        matrix.clear();                         // clearing  chip memory
        matrix.writeDigitNum(0,(h/10)) ;        // writing first digit of hour
        matrix.writeDigitNum(1,(h%10)) ;         // writing second digit of hour
        matrix.writeDigitNum(3,(m/10)) ;         // writing first digit of min
        matrix.writeDigitNum(4,(m%10)) ;         // writing second digit of min
        matrix.writeDigitNum(2,bl) ;             // blinking dot
        matrix.writeDisplay();                   // displaying
      
        bl++;  //dot increament
 
    if(bl==9)
    bl=0;
 
    if(flag==24)                      
    flag=0; 
    
    delay(1000); 
    if(s==60)          // second
      { 
         s=0; 
         m=m+1; 
      } 
 
   if(m==60)           // minute 
    { 
      m=0; 
      h=h+1; 
      flag=flag+1; 
    } 

   if(h==13)          // hour
    { 
    h=1; 
    } 
 
//-------Time         // setting-------// 
  
    state1=digitalRead(hs); 
    if(state1==0) 
      { 
        h=h+1; 
        flag=flag+1; 
        if(flag<12)
            Serial.print("AM"); 
        if(flag==12)
            Serial.print("PM"); 
        if(flag>12)
            Serial.print("PM"); 
        if(flag==24)  
            flag=0; 
        if(h==13)h=1; 
      } 

    state2=digitalRead(ms); 

    if(state2==0)
      { 
        s=0; 
        m=m+1; 
      }  
} 
