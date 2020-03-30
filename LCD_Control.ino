#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal_I2C.h>


//code for control
char ampOutput[] = "Capacity:   %";
char freqOutput[] = "Frequency:   BMP";

unsigned int ampIn;
unsigned int freqIn;
const unsigned int  FREQPIN = A2;
const unsigned int AMPPIN = A1;


// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
 // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  lcd.begin();
  lcd.backlight();
}
//key denote index of number position
//insert number to character
//type 0 is amp type 1 is freq
void convertChar(int number, char * text, int index, bool type){
  //check for each digit
  char digits[3];
  digits[0] = (number%1000)/100;
  digits[1] = (number%100)/10;
  digits[2] = (number%10);
  for(char i=0;i<2;i++){
    if(digits[i]!=0)
      break;
    digits[i]=-16;
  }
  
  if(type){
    text[index]= digits[0]+'0';
    text[index+1]= digits[1]+'0';
    text[index+2]= digits[2]+'0';
  }else{
    text[index]=digits[1]+'0';
    text[index+1]=digits[2]+'0';
  }
  
}


void loop() {
  //read val in for the system
  ampIn = analogRead(AMPPIN);
  freqIn = analogRead(FREQPIN);
  
 //properly map the values
  //added one to 1023 in order to approximate value and eliminate maximum
  freqIn = map(freqIn,0, 1024, 10, 31);
  ampIn = map(ampIn,0, 1024, 0, 11);
  //convert ampIn to scale 
  ampIn = ampIn *10;
  
  convertChar(ampIn, ampOutput, 9,true);
  convertChar(freqIn, freqOutput, 10,false);
  
  
  //print output to capacity and frequency
  lcd.setCursor(0, 0);
  lcd.print(ampOutput);
  Serial.println(ampOutput);
  Serial.println(freqOutput);
  lcd.setCursor(0, 1);
  lcd.print(freqOutput);
}
 
