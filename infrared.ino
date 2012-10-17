float aRead;
float distance;
float cm_distance;
float in_distance;

int analogPIN = 3;

void setup()
{
 Serial.begin(9600); 
}
void loop()
{
  distance =  5.0 / 1023;
  cm_distance = (distance * 0.42 ) - 2.21;
  in_distance = cm_distance * 2.54;
  aRead = analogRead(analogPIN);  
  Serial.println(aRead);
  
  Serial.print("Distances in CM: ");
  Serial.println(cm_distance);  
  Serial.println();

  Serial.print("Distances in IN: ");
  Serial.println(in_distance);  
  delay(1000);
}
