  /* Pybot drawing robot by Ekaterina Shkrabova for UChicago Pybot, 2013
  robot is controlled by IR ranger, a bluetooth remote, or photosensor.
  remote controls - "l" left "r" right "f" forward "b" back
  
  */
  
  #include <Servo.h>

  Servo myservo;  // create servo object to control a servo 
  
  int pos = 90;    // variable to store the servo position
  int servo_step=2;  //servo spetsize
  char signal;     //stores message from remote
  char val='n';
  
  int IRpin = A0;    //infrared pin
  int LDR_left=A5;    //LDR1 pin
  int LDR_right=A6;    //LDR2 pin
  int LDR_center=0;    //center between the LDR sensors
  int samples=10;
  int deadband=30;
  
  const int switchPin = 2;    // switch input
  const int rmotor1Pin = 4;    // H-bridge leg 1 (pin 2, 1A) right motor
  const int rmotor2Pin = 5;    // H-bridge leg 2 (pin 7, 2A) right motor
  const int renablePin = 3;    // H-bridge enable pin right motor
  
  const int lmotor1Pin = 8;    // H-bridge leg 1 (pin 2, 1A) left motor
  const int lmotor2Pin = 9;    // H-bridge leg 2 (pin 7, 2A) left motor
  const int lenablePin = 10;    // H-bridge enable pin  left motor
  const int ledPin = 13;      // LED 
  
  float d, d0, d1 =0;        //distance variable
  
  
 void setup ()
 {
   
   myservo.attach(A1);    //attaching the servo to pin A1 as a servo object
   
   //Bluetoth SLAVE config
  Serial.begin(115200);   // start serial communication at 115200 baud for the BT
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,0");
  delay(100);
  Serial.println("---");
  
  //set pins used as outputs
  pinMode(rmotor1Pin, OUTPUT); 
  pinMode(rmotor2Pin, OUTPUT); 
  pinMode(renablePin, OUTPUT);
  pinMode(lmotor1Pin, OUTPUT); 
  pinMode(lmotor2Pin, OUTPUT); 
  pinMode(lenablePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //set LDR pins as input
  pinMode(IRpin, INPUT);
  pinMode(LDR_left, INPUT); 
  pinMode(LDR_right, INPUT);

  // set enablePin high so that motor can turn on:
  digitalWrite(renablePin, HIGH);
  digitalWrite(lenablePin, HIGH); 
  
   //Blink LED 5 tiimes as the setup occurs. 
  blink(ledPin, 5, 1000);
   
 }
 
 void loop(){
   
  //set the servo straight, get IR sensor distance
  myservo.write(pos);
  d = getDistance();
  delay(10);
  
  if( Serial.available() )        // if data is available to read
  {
    val = Serial.read();
    if (val == 'f'){
      Serial.println("f");
      rightForward();
      leftForward();
    
    }
      else if (val == 'b'){
        Serial.println("b");
        rightBackward();
        leftBackward();
    
    }
     else if (val == 'l'){
       Serial.println("l");
       leftBackward();
       rightForward();
     
  }
    else if (val =='r'){
      Serial.println("r");
      leftForward();
      rightBackward(); 
    
  }
    
    if( val == '0')
    {
      Serial.println("remote");
     // rightStop();
      //leftStop();     
      //remoteListen();
    }
    else if (val == '1'){
      Serial.println("1");
      lightFollow();
    }
    else if (val == '2'){
      Serial.println("2");
      irAvoid();
    }
    delay(50);
  }
 }
 
 void blink(int whatPin, int howManyTimes, int milliSecs){
    int i = 0;
    for ( i = 0; i < howManyTimes; i++) {
      digitalWrite(whatPin, HIGH);
      delay(milliSecs/2);
      digitalWrite(whatPin, LOW);
      delay(milliSecs/2);
    }
}


void remoteListen(){
  char signal;
  
  signal = Serial.read();
  
  if (signal == 'f'){
    Serial.println("f");
    rightFor();
    leftFor();
  }
  else if (signal == 'b'){
    Serial.println("b");
    rightBack();
    leftBack();
  }
  else if (signal == 'l'){
     Serial.println("l");
     leftBack();
     rightFor();
     
  }
  else if (signal =='r'){
    Serial.println("r");
    leftFor();
    rightBack(); 
    

  }
  else{
  leftStop();
  rightStop();
  }
  delay(50);
}

void lightFollow(){
  //Based on Justin Jureller's code for sunflower, pybot 2012 
  
  int R_LDR_val=0;   //stores LDR values
  int L_LDR_val=0;
  for(int i=0;i<=samples;i++){
    R_LDR_val=R_LDR_val+analogRead(LDR_right); 
    L_LDR_val=L_LDR_val+analogRead(LDR_left);
  }
  
  R_LDR_val=(R_LDR_val/samples);    //take average
  L_LDR_val=(L_LDR_val/samples);
  
  R_LDR_val=map(R_LDR_val,0,700,0,1000); 
  L_LDR_val=map(L_LDR_val,0,800,0,1000);
  LDR_center=(L_LDR_val-R_LDR_val);
  
  if(LDR_center<0 && abs(LDR_center) > deadband){
    rightBackward(); //deadband prevents oscillation around 0 
    leftForward();
  }
  else if((LDR_center< 0) && (abs(LDR_center) > deadband)){
    leftBackward; //deadband prevents oscillation around 0
    rightForward;
  }
  else{
   leftForward();
   rightForward();
  }
  
  delay(10);
  rightStop();
  leftStop();
}


void irAvoid(){
  
  myservo.write(pos);
  d = getDistance();
  delay(10);
  if (d <= 20){    //gotta go back, this is wa-ay too close
     rightStop();
     leftStop();
     blink(ledPin, 1, 100);       //scream, of sorts
     delay(100);
     rightBackward();
     leftBackward(); 
     delay(400);
     
     Serial.println("way too close");
    }
    
    
  else if (d < 40 && d >20){    //too close, let's look both ways and get outta here
     blink(ledPin, 3, 15); 
     
     Serial.println("too close");
     
     myservo.write(pos);
     delay(50);
     rightStop();
     leftStop();
     delay(100);
     myservo.write(180);
     delay(250);
     d0=getDistance();      //get reading from left
     myservo.write(pos);
     delay(250);
     myservo.write(0);
     delay(250);
     d1=getDistance();    //get reading from right
     if( d0-d1>=0){    //the distance is greater on the left, turn left
     
         Serial.println("turning left");
         myservo.write(pos);
         delay(50);
         leftBackward();
         rightForward();
         delay(100);
         leftStop();
         rightStop();
     }
      else {                //the distance is greater on the right, turn right
      
        Serial.println("turning right");
        myservo.write(pos);
        delay(50);
        leftForward();
        rightBackward(); 
        delay(100);
        leftStop();
        rightStop();
       }
     delay(300); 
    }
    
  else if (d >= 40){    //go ahead
       Serial.println("straight");
     rightForward();
     leftForward(); 
    } 
    
  }
 
 void rightForward(){
    digitalWrite(rmotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(rmotor2Pin, HIGH);  // set leg 2 of the H-bridge high
      delay(25);
      digitalWrite(rmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(rmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(3);
  }
void leftForward(){
      digitalWrite(lmotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(lmotor2Pin, HIGH);  // set leg 2 of the H-bridge high
      delay(25);
      digitalWrite(lmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(lmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(3);
      
  } 
void rightBackward(){
      digitalWrite(rmotor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(rmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(25);
      digitalWrite(rmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(rmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(3);
      
  } 
void leftBackward(){
      digitalWrite(lmotor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(lmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(25);
      digitalWrite(lmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(lmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(3);
 }
 void rightBack(){
      digitalWrite(rmotor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(rmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(100);
     
  } 
void leftBack(){
      digitalWrite(lmotor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(lmotor2Pin, LOW);   // set leg 2 of the H-bridge low
      delay(100);
}
void rightFor(){
    digitalWrite(rmotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(rmotor2Pin, HIGH);  // set leg 2 of the H-bridge high
      delay(100);
  }
void leftFor(){
      digitalWrite(lmotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(lmotor2Pin, HIGH);  // set leg 2 of the H-bridge high
      delay(100);
}
void leftStop(){
      digitalWrite(lmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(lmotor2Pin, LOW);   // set leg 2 of the H-bridge low
 }
void rightStop(){
      digitalWrite(rmotor1Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(rmotor2Pin, LOW);   // set leg 2 of the H-bridge low
 }
float getDistance(){
    float volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S 
    return distance;
 }  
