

//Digital pin 6 for reading in the pulse width from the MaxSonar device.
//This variable is a constant because the pin will not change throughout execution of this code.
#include <Servo.h>//Sam Wytoski Joystick
#include <SPI.h>//Marshal's Display
#define xinN 0//David Calawa Gyro 
const int joystick_xPin = A1;//Sam Wytoski Joystick 
const int joystick_yPin = A2;  
Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
const int buttonPin = 2;     // the number of the pushbutton pin Sam Wytoski
const int slaveSelectPin = 10;//Marshal's Display
const int pwPin = 6; //Sonar
const int analogPIN = 3;//Marshal'sInfared
//variables needed to store values
float pulse,inches,cm,aRead,distance,cm_distance,in_distance; 
int valuexwide,valuexnarrow,valueywide,valueynarrow,xwide,xnarrow,ywide,ynarrow,xinW,yinN,yinW;//David Calawa Gyro




void setup() { 
  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
  pinMode(pwPin, INPUT);//Sonar
  pinMode (slaveSelectPin, OUTPUT);//Marshal's Display
  SPI.begin();//Marshal's Display
  SPI.setBitOrder(MSBFIRST);//Marshal's Display
  SPI.setDataMode(SPI_MODE0);//Marshal's Display
  SPI.setClockDivider(SPI_CLOCK_DIV128);//Marshal'sDisplay
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object. servo x Sam Wytoski's joystick
  servo2.attach(5);  // attaches the servo on pin 5 to the servo object. servo y Sam Wytoski's Joystick
  pinMode(buttonPin, INPUT); //Sam Wytoski's Joystick
  //pinMode(xinN, INPUT);
  //xinW = 0;//Gyro David Calawa
  //yinW = 0;//Gyro David Calawa
  //xinN = 14;//Gyro David Calawa
  //yinN = 0;//Gyro David Calawa
 } 
 
void Gyro(){//David Calawa's code
  valuexwide = analogRead(xinW);
  xwide = map(valuexwide, 71, 481, -500, 500);
  valueywide = analogRead(yinW);
  ywide = map(valueywide, 71, 481, -500, 500);

  valuexnarrow = analogRead(xinN);
  xnarrow = map(valuexnarrow, 71, 481, -110, 110);
  
  valueynarrow = analogRead(yinN);
  ynarrow = map(valueynarrow, 71, 481, -110, 110);
  
  
  //Serial.print(xwide);
  //Serial.print(ywide);
  //Serial.print(xnarrow);
  //Serial.print(ynarrow);
  //Serial.println();

}

void Joystick(){//Sam Wytoski's Joystick code 
//buttonState = digitalRead(buttonPin);
//int buttonState = 0;         // variable for reading the pushbutton status
  int joystick_x;  
  int joystick_y;  
  joystick_x = map(analogRead(joystick_xPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  joystick_y = map(analogRead(joystick_yPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  servo1.write(joystick_x);                  // sets the servo position according to the scaled value 
  servo2.write(joystick_y);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
//if (buttonState == HIGH) {     
//  turn LED on:    
//  digitalWrite(ledPin, HIGH);  
// } 
// else {
//   turn LED off:
//   digitalWrite(ledPin, LOW); 
//        }
}

void Display(){//Code FROM MARSHAL LESLIE
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(1);
  SPI.transfer(2);
  SPI.transfer(3);
  SPI.transfer(4);
  digitalWrite(slaveSelectPin,HIGH);
}

void Infared(){//CODE FROM MARSHAL LESLIE
  distance =  5.0 / 1023;
  cm_distance = (distance * 0.42 ) - 2.21;
  in_distance = cm_distance * 2.54;
  aRead = analogRead(analogPIN);  
 // Serial.println(aRead);
  //Serial.print("Distances in CM: ");
  //Serial.println(cm_distance);  
 // Serial.println();
 // Serial.print("Distances in IN: ");
 // Serial.println(in_distance);  
}

void Sonar(){
  //Shannon Busher CS272 Dr. Morse
  //Feel free to use this code.
  //Please be respectful by acknowledging the author in the code if you use or modify it.
  //Author: Bruce Allen
  //Date: 23/07/09
  //note connect Arduino pin 6 to pw on sonar
  // +5v
  //grnd

  //Used to read in the pulse that is being sent by the MaxSonar device.  //Pulse Width representation with a scale factor of 147 uS per Inch.  
  pulse = pulseIn(pwPin, HIGH);
    //Serial.println(pulse);
  //147uS per inch
  inches = pulse/147;
  //change inches to centimetres
  cm = inches * 2.54;
 //Serial.print(inches);
//  Serial.print("in, ");
 // Serial.print(cm);
 // Serial.print("cm");
  //Serial.println();
}

void loop() { 
  Sonar();//Shannnon Busher
  Infared();//Marshal Leslie
  Display();//Marshal Leslie
  Joystick();//Sam Wytoski
  Gyro();//David Calawa
  Serial.print(" ");
  Serial.print(aRead);
  Serial.print(" ");
  Serial.print(pulse);
  Serial.print(" ");
  Serial.print(valuexnarrow);
 Serial.print("\n");
} 


