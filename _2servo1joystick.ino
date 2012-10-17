#include <Servo.h>
const int joystick_xPin = A1;  
const int joystick_yPin = A2;  
Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
//const int buttonPin = 2;     // the number of the pushbutton pin

void setup()  
{  
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object. servo x
  servo2.attach(5);  // attaches the servo on pin 5 to the servo object. servo y
//  pinMode(buttonPin, INPUT);     
}
void loop()
{  
//  buttonState = digitalRead(buttonPin);
//  int buttonState = 0;         // variable for reading the pushbutton status
  int joystick_x;  
  int joystick_y;  
  joystick_x = map(analogRead(joystick_xPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  joystick_y = map(analogRead(joystick_yPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  servo1.write(joystick_x);                  // sets the servo position according to the scaled value 
  servo2.write(joystick_y);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
//    if (buttonState == HIGH) {     
    // turn LED on:    
//    digitalWrite(ledPin, HIGH);  
// } 
//  else {
    // turn LED off:
//    digitalWrite(ledPin, LOW); 
//        }
}

//int jStick_x;  //  var for position of servo x
//int jStick_y;  //  var for position of servo y
//if 
