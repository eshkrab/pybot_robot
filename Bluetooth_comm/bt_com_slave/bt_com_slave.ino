//Bluetooth Communication tester, using RGB LED and toggle switches
//this is the SLAVE code, that toggles colors on RGB 
//by another Arduino hooked up to three toggle switches
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
char val;  // variable to store command from bt


void setup()
{ 
  pinMode(redPin, OUTPUT);  //setting the LED pins as OUT
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  
  // BT SLAVE code
  Serial.begin(115200);   // start serial communication at 115200 baud for the BT
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,0");
  delay(100);
  Serial.println("---");

  
}
void loop()
{
  if( Serial.available() )       // if data is available to read
  {val = Serial.read();
             // read it and store it in 'val'
 
    if( val == '0' )               
    {
      analogWrite(redPin, 255);  // red
     // delay(50);                  // waits for a second
      Serial.println("red off");
    }

    if( val == '1' )               
    {
        analogWrite(greenPin, 255);  // green
      //delay(50);                  // waits for a second
      Serial.println("green off");
    }
    if( val == '2' )               
    {
      analogWrite(bluePin, 255);  // blue
     // delay(50);                  // waits for a second
      Serial.println("blue off");
    }
    
    
     if( val == '3' )               
    {
      analogWrite(redPin, 0);  // red
      delay(50);                  // waits for a second
      Serial.println("red on");
    }

    if( val == '4' )               
    {
        analogWrite(greenPin, 0);  // green
      //delay(50);                  // waits for a second
      Serial.println("green on");
    }
    if( val == '5' )               
    {
      analogWrite(bluePin, 0);  // blue
      //delay(50);                  // waits for a second
      Serial.println("blue on");
    }
  }
  delay(50);
}


