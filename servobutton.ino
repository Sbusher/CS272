#include <Servo.h>//Sam Wytoski Joystick
const int joystick_xPin = A1;//Sam Wytoski Joystick 
const int joystick_yPin = A2;  
Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
const int buttonPin = 2;     // the number of the pushbutton pin Sam Wytoski
const int Relay = 3;//relay digital pin

//function prototype
boolean buttonPressed(int);
void joystick();

void setup(){
  pinMode(Relay, OUTPUT); //relay    
  //Set Pin3 as output}
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object. servo x Sam Wytoski's joystick
  servo2.attach(5);  // attaches the servo on pin 5 to the servo object. servo y Sam Wytoski's Joystick
  pinMode(buttonPin, INPUT); //Sam Wytoski's Joystick
}
Void loop(){
  Joystick();
  if (buttonPressed(buttonPin)){
    //boolean is returned for button pressed but is not used at this time
  }
}

void Joystick(){//Sam Wytoski's Joystick code 
  int joystick_x;  
  int joystick_y;  
  joystick_x = map(analogRead(joystick_xPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  joystick_y = map(analogRead(joystick_yPin), 0, 1023, 1, 180);  // 20 was original instead of 180
  servo1.write(joystick_x);                  // sets the servo position according to the scaled value 
  servo2.write(joystick_y);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}

boolean buttonPressed(int button){
  boolean pressed=false;
  if(digitalRead(button)==low)
  {
    delay(5);
    if(digitalRead(button)==low){
      pressed=true;
      //turn on relay to fire/turn on laser
      digitalWrite(Relay,HIGH);
    }
  }
  if(!pressed){
      return(false);
  }
  While(digitalRead(button)==low){
   //waiting for button to be released    
   joystick();//allow for more movement / aim to target :)
  }
  //Button is released, so turn of relay/laser
  digitalWrite(Relay,LOW);
  return true;
}

