int remote_switch = 8; //switch1 pin
int IR_switch = 9;  //switch2
int light_switch = 10;  //switch3

int buttonLeft = 3;
int buttonForward = 5;
int buttonRight = 6;
int buttonBack = 4;

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
  Serial.println("C,0006664EE472");  //the specific MAC address for the bt module
  delay(100);
  Serial.println("---");
  
  //pin setup code
  pinMode(13, OUTPUT); //LED on pin 13
  pinMode(remote_switch, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
  pinMode(IR_switch, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
  pinMode(light_switch, INPUT_PULLUP); //monitor pin state, enable pullups to make pin high
}

void loop()
{ 
 if (true ){//Serial.available() > 0) {
    
    if (checkPressed(remote_switch))
    {
      Serial.println("0");
      if (checkPressed(buttonLeft))
        {
          Serial.println('l');   
        }
        
      if (checkPressed(buttonForward))
        {
          Serial.println('f');  
        }
       
      if (checkPressed(buttonRight))
        {
          Serial.println('r');   
         
        }
      if (checkPressed(buttonBack))
        {
          Serial.println('b');    
         }
    
    }
    else if (checkPressed(IR_switch))
    {
      Serial.println("1");
    }
    else if (checkPressed(light_switch))
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
