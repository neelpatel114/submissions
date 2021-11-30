/*
 * Author: Automatic Addison
 * Website: https://automaticaddison.com
 * Description: ROS node that publishes the accumulated ticks for each wheel
 * (right_ticks and left_ticks topics) using the built-in encoder 
 * (forward = positive; reverse = negative) 
 */
 
#include <ros.h>
#include <std_msgs/Int16.h>
 
// Motor encoder output pulses per 360 degree revolution (measured manually)
#define ENC_COUNT_REV 620

// Handles startup and shutdown of ROS
ros::NodeHandle nh;
 
// Encoder output to Arduino Interrupt pin. Tracks the tick count.
#define ENC_IN_LEFT_A 2
#define ENC_IN_RIGHT_A 3
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_LEFT_B 4
#define ENC_IN_RIGHT_B 11
 
// True = Forward; False = Reverse
boolean Direction_left = true;
boolean Direction_right = true;
 
// Minumum and maximum values for 16-bit integers
const int encoder_minimum = -32768;
const int encoder_maximum = 32767;
 
// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;

// Keep track of the number of wheel ticks
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

std_msgs::Int16 rpm_right;
ros::Publisher rpm_rightPub("RPM", &rpm_right);

std_msgs::Int16 ang_velocity_right;
ros::Publisher ang_velocity_rightPub("Ang Velocity R", &ang_velocity_right);

std_msgs::Int16 ang_velocity_right_deg;
ros::Publisher ang_velocity_degreePub("And Velocity Deg R", &ang_velocity_right_deg);


// 100ms interval for measurements
const int interval = 100;
long previousMillis = 0;
long currentMillis = 0;
 


 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;

// Increment the number of ticks
void right_wheel_tick() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
     
    if (right_wheel_tick_count.data == encoder_maximum) {
      right_wheel_tick_count.data = encoder_minimum;
    }
    else {
      right_wheel_tick_count.data++;  
    }    
  }
  else {
    if (right_wheel_tick_count.data == encoder_minimum) {
      right_wheel_tick_count.data = encoder_maximum;
    }
    else {
      right_wheel_tick_count.data--;  
    }   
  }
}
 
// Increment the number of ticks
void left_wheel_tick() {
   
  // Read the value for the encoder for the left wheel
  int val = digitalRead(ENC_IN_LEFT_B);
 
  if(val == LOW) {
    Direction_left = true; // Reverse
  }
  else {
    Direction_left = false; // Forward
  }
   
  if (Direction_left) {
    if (left_wheel_tick_count.data == encoder_maximum) {
      left_wheel_tick_count.data = encoder_minimum;
    }
    else {
      left_wheel_tick_count.data++;  
    }  
  }
  else {
    if (left_wheel_tick_count.data == encoder_minimum) {
      left_wheel_tick_count.data = encoder_maximum;
    }
    else {
      left_wheel_tick_count.data--;  
    }   
  }
}
 
void setup() {
 
  // Set pin states of the encoder
  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
 
  // Every time the pin goes high, this is a tick
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_tick, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_tick, RISING);
 
  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  nh.advertise(rpm_rightPub);
  nh.advertise(ang_velocity_rightPub);
  nh.advertise(ang_velocity_degreePub);
}
 
void loop() {
   
  // Record the time
  currentMillis = millis();
 
  // If 100ms have passed, print the number of ticks
  if (currentMillis - previousMillis > interval) {
     
    previousMillis = currentMillis;
    // Calculate revolutions per minute
    rpm_right.data = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
    ang_velocity_right.data = rpm_right.data * rpm_to_radians;   
    ang_velocity_right_deg.data = ang_velocity_right.data * rad_to_deg;

    rightPub.publish( &right_wheel_tick_count );
    leftPub.publish( &left_wheel_tick_count );
    rpm_rightPub.publish(&rpm_right);
    ang_velocity_rightPub.publish(&ang_velocity_right);
    ang_velocity_degreePub.publish(&ang_velocity_right_deg);

    right_wheel_pulse_count = 0;
    nh.spinOnce();
  }
}