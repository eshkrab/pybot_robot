//zoomkat servo-LED button toggle test 11-12-2012


int switch1 = 3; //switch1 pin
int switch2 = 4;  //switch2
int switch3 = 5;  //switch3
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
  
  s1 = digitalRead(switch1);
  s2 = digitalRead(switch2);
  s3 = digitalRead(switch3);
// if (Serial.available() > 0) {
    if (s1 == LOW)
    {
      Serial.println("3");   // set the LED on
      //digitalWrite(13, HIGH);
     
    }
    else if (s1 == HIGH)
    {
     // digitalWrite(13, LOW);
      Serial.println("0");    // set the LED off
      
    }
    if (s2 == LOW)
    {
      Serial.println("4");   // set the LED on
      digitalWrite(13, HIGH);
     
    }
    else if (s2 == HIGH)
    {
      //digitalWrite(13, LOW);
      Serial.println("1");    // set the LED off
      
    }
    if (s3 == LOW)
    {
      Serial.println("5");   // set the LED on
     // digitalWrite(13, HIGH);
     
    }
    else if (s3 == HIGH)
    {
     // digitalWrite(13, LOW);
      Serial.println("2");    // set the LED off
      
    }
    delay(500);  //delay for debounce
  //}
}
