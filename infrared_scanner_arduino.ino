#include <Servo.h>
int analogPin = A3;
int vaal=0;// IR sensor on this pin
const int SIZE = 100;
int points[SIZE];
int numberOfPoints = 0;

Servo myservo;
int pos = 60;

//int analogread(int readPin, int triggerPin); //function prototype

void setup()
{
  myservo.attach(9);
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}

void loop()
{ 

  if(Serial.available() > 0)
  {

    String command = Serial.readString();
    
    if(command == "scan")
    {
      vaal=analogRead(analogPin);
      vaal = vaal;

        for (pos = 60; pos <= 160; pos += 1) 
        {
          myservo.write(pos);  // tell servo to go to position in variable 'pos'
          delay(50);    // waits 15ms for the servo to reach the position
          vaal=analogRead(analogPin);
          points[pos-60] = vaal;
          numberOfPoints += 1;
          Serial.print(String(","));
          Serial.print(String(points[pos-60]));
        }
        for (pos = 160; pos > 60; pos -= 1) 
        { 
          myservo.write(pos); // tell servo to go to position in variable 'pos'
          delay(10);                       // waits 15ms for the servo to reach the position
        }
    }

    else if(command == "test")
    {
      
    }
  }
  
}
