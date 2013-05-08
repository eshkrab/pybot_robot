int switch1 = 8; //switch1 pin
int switch2 = 9;  //switch2
int switch3 = 10;  //switch3

int buttonLeft = 6;
int buttonForward = 5;
int buttonRight = 4;
int buttonBack = 3;

int s1 = 0;  //switch value variable
int s2 = 0;
int s3 = 0;

void setup()
{
 
  //BT MASTER setup code
  Serial.begin(115200);
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,1");  delay(100);
  Serial.println("C,0006664859F6");  //the specific MAC address for the bt module
  delay(100);
  Serial.println("---");
  
  //pin setup code
  pinMode(13, OUTPUT); //LED on pin 13
  pinMode(switch1, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
  pinMode(switch2, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
  pinMode(switch3, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
}

void loop()
{ 
 if (true ){//Serial.available() > 0) {
    
    if (checkPressed(switch1))
    {
      Serial.println("0");
      if (checkPressed(buttonLeft))
        {
          Serial.println('l');   // set the LED on
        }
        
        if (checkPressed(buttonForward))
        {
          Serial.println('f');   // set the LED on
        }
       
        if (checkPressed(buttonRight))
        {
          Serial.println('r');   // set the LED on
         
        }
        if (checkPressed(buttonBack))
        {
          Serial.println('b');    // set the LED off 
         }
    
    }
    if (checkPressed(switch2))
    {
      Serial.println("1");
    }
    if (checkPressed(switch3))
    {
      Serial.println("2");
    }
    delay(300);  //delay for debounce
  }
}
boolean checkPressed (int button){
  int buttonState = digitalRead(button);
  
  if (buttonState == LOW) {
    return true;
  }
  else {
    return false;
  }
}
