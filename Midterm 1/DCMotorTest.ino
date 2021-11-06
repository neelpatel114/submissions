
/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorTwo = AFMS.getMotor(2);
Adafruit_DCMotor *myMotorThree = AFMS.getMotor(3);
Adafruit_DCMotor *myMotorFour = AFMS.getMotor(4);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

//Global Vars
  int pin_1A = 11;
  int pin_1B = 10;
  int pin_2A = 9;
  int pin_2B = 8;
  int pin_3A = 7;
  int pin_3B = 6;
  int pin_4A = 5;
  int pin_4B = 4;


void forward(int time,int speed){
  myMotor->run(FORWARD);
  myMotorTwo->run(FORWARD);
  myMotorThree->run(FORWARD);
  myMotorFour->run(FORWARD);

  for(int i = 0; i < time; i++){ 
    myMotor->setSpeed(255);
    myMotorTwo->setSpeed(255);
    myMotorThree->setSpeed(255);
    myMotorFour->setSpeed(255);
    delay(100);
  }
}

void backward(int time,int speed){
  myMotor->run(BACKWARD);
  myMotorTwo->run(BACKWARD);
  myMotorThree->run(BACKWARD);
  myMotorFour->run(BACKWARD);

  for(int i = 0; i < time; i++){ 
    myMotor->setSpeed(255);
    myMotorTwo->setSpeed(255);
    myMotorThree->setSpeed(255);
    myMotorFour->setSpeed(255);
    delay(100);
  }
}

void right(int time,int speed){
  myMotor->run(FORWARD);
  myMotorTwo->run(BACKWARD);
  myMotorThree->run(FORWARD);
  myMotorFour->run(BACKWARD);

  for(int i = 0; i < time; i++){ 
    myMotor->setSpeed(speed);
    myMotorTwo->setSpeed(speed);
    myMotorThree->setSpeed(speed);
    myMotorFour->setSpeed(speed);
    delay(100);
  }

}

void left(int time,int speed){
  myMotor->run(BACKWARD);
  myMotorTwo->run(FORWARD);
  myMotorThree->run(BACKWARD);
  myMotorFour->run(FORWARD);

  for(int i = 0; i < time; i++){ 
    myMotor->setSpeed(speed);
    myMotorTwo->setSpeed(speed);
    myMotorThree->setSpeed(speed);
    myMotorFour->setSpeed(speed);
    delay(100);
  }

}

void stop(){
  myMotor->run(RELEASE);
  myMotorTwo->run(RELEASE);
  myMotorThree->run(RELEASE);
  myMotorFour->run(RELEASE);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test! - Stright");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  


  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  myMotorTwo->setSpeed(255);
  myMotorThree->setSpeed(255);
  myMotorFour->setSpeed(255);
  myMotor->run(FORWARD);
  myMotorTwo->run(FORWARD);
  myMotorThree->run(FORWARD);
  myMotorFour->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myMotorTwo->run(RELEASE);
  myMotorThree->run(RELEASE);
  myMotorFour->run(RELEASE);
  
}

void loop() {
  delay(5000);
  //F1
  Serial.println("Forward");
  forward(15,255);
  stop();
  //L2
  Serial.println("Left");
  left(10,255);
  stop();
  //F3
  Serial.println("Forward");
  forward(15,255);
  stop();
  //L4
  Serial.println("Left");
  left(10,255);
  stop();
  //F5
  Serial.println("Forward");
  forward(15,255);
  stop();
  //R6
  Serial.println("Right");
  right(12,255);
  stop();
  //F7
  Serial.println("Forward");
  forward(15,255);
  stop();
  //R8
  Serial.println("Right");
  right(12,255);
  stop();
  //F9
  Serial.println("Forward");
  forward(15,255);
  stop();
  //R10
  Serial.println("Right");
  right(12,255);
  stop();
  //F11
  Serial.println("Forward");
  forward(15,255);
  stop();
  //R12
  Serial.println("Right");
  right(12,255);
  stop();
  //F13
  Serial.println("Forward");
  forward(15,255);
  stop();
  //L14
  Serial.println("Left");
  left(10,255);
  stop();
  //F15
  Serial.println("Forward");
  forward(15,255);
  stop();
  //L16
  Serial.println("Left");
  left(10,255);
  stop();
  


}