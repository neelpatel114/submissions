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

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test! - Stright");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  Serial.println("Turn Right.");
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
  uint8_t i;

  Serial.println("Circle");

  myMotor->run(BACKWARD);
  myMotorTwo->run(FORWARD);
  myMotorThree->run(BACKWARD);
  myMotorFour->run(FORWARD);
  
  myMotor->setSpeed(100);
  myMotorTwo->setSpeed(200);
  myMotorThree->setSpeed(100);
  myMotorFour->setSpeed(200);

}