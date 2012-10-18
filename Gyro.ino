//David Calawa
//CS-272
//Scot Morse
//Lab2 #4
//10-7-2012

#define xinN 14

//int valuexwide;
int valuexnarrow;
//int valueywide;
//int valueynarrow;
//int xwide;
int xnarrow;
//int ywide;
//int ynarrow;
//int xinN;
//int xinW;
//int yinN;
//int yinW;

void setup()
{
  Serial.begin(9600);
  //xinW = 0;
  //yinW = 0;
  //xinN = 14;
  //yinN = 0;
}

void loop()
{
  /*
  valuexwide = analogRead(xinW);
  xwide = map(valuexwide, 71, 481, -500, 500);
 
  valueywide = analogRead(yinW);
  ywide = map(valueywide, 71, 481, -500, 500);
  */
  valuexnarrow = analogRead(xinN);
  xnarrow = map(valuexnarrow, 71, 481, -110, 110);
  /*
  valueynarrow = analogRead(yinN);
  ynarrow = map(valueynarrow, 71, 481, -110, 110);
  */
  
  //Serial.print(xwide);
  //Serial.print(ywide);
  Serial.print(xnarrow);
  //Serial.print(ynarrow);
  Serial.println();
  delay(10);
}
