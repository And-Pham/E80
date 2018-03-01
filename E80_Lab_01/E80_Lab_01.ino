/********
Default E80 Lab 01 
Current Author: Christopher McElroy (cmcelroy@g.hmc.edu) '19 (contributed in 2017)
Previous Contributors:  Josephine Wong (jowong@hmc.edu) '18 (contributed in 2016)
                        Apoorva Sharma (asharma@hmc.edu) '17 (contributed in 2016)
*/

/* Libraries */

// general
#include <Arduino.h>
#include <Wire.h>
#include <Pinouts.h>

// 80-specific
#include <SensorGPS.h>
#include <SensorIMU.h>
#include <ADCSampler.h>
#include <MotorDriver.h>
#include <Logger.h>
#include <Printer.h>


// template library
#include <LED.h>


/* Global Variables */

// Motors
MotorDriver motorDriver;

// IMU
SensorIMU imu;

// Logger
Logger logger;
bool keepLogging = true;

// Printer
Printer printer;

// Led
LED led;

// loop start recorderpi
int loopStartTime;




void setup() {
  printer.init();

  /* Initialize the Logger */
  logger.include(&imu);
  logger.include(&motorDriver);
  logger.init();

  /* Initialise the sensors */
  imu.init();

  /* Initialize motor pins */
  motorDriver.init();

  /* Done initializing, turn on LED */
  led.init();

  /* Keep track of time */
  printer.printMessage("Starting main loop",10);
  loopStartTime = millis();
}





void loop() {

  /* set the motors to run based on time since the loop started */
  /* loopStartTime is in units of ms */
  /* The motorDriver.drive function takes in 4 inputs arguments m1_power, m2_power, m3_power, m4_power: */
  /*       void motorDriver.drive(int m1_power, int m2_power, int m3_power, int m4_power) */
  /* the value of m!_power can range from -255 to 255 */
  /* Note: we typically avoid m3, it hasn't worked well in the past */

  /* The following example will turn on m2 for between seconds 4 and 8 */
  int currentTime = millis() - loopStartTime;

  /* Adjust motor thrust based on timing 
  if (currentTime > 4000 && currentTime <8000)
    motorDriver.drive(0,120,0,0);
  else 
    motorDriver.drive(0,0,0,0);*/
    /*turn off motors for 2sec*/

//
////do nothing for first 52 seconds
if (currentTime < 12000 )
  motorDriver.drive(0, 0,0,0);
//  
////positive down
if (currentTime >12000 && currentTime <= 18000)
  motorDriver.drive(127,0,0,0);
//  
//
////negative down
if (currentTime > 18000 && currentTime <= 24000)
  motorDriver.drive(-127,0,0,0);
//
////positive across
if (currentTime > 24000 && currentTime <= 33000)
  motorDriver.drive(0,0,127,127);
//
////negative across
if (currentTime > 33000 && currentTime <= 42000)
  motorDriver.drive(0,0,-127,-127);
//
////positive uppity up 
if (currentTime > 42000 && currentTime <= 50000)
  motorDriver.drive(-127,0,0,0);
//  
if (currentTime > 50000)
  motorDriver.drive(0,0,0,0);


  
////do nothing for first 12 seconds
//if (currentTime < 12000 )
//  motorDriver.drive(0, 0,0,0);
//
////positive down
//if (currentTime >12000 && currentTime <18000)
//  motorDriver.drive(0,127,0,0);
//
////negative down
//if (currentTime >18000 && currentTime <24000)
//  motorDriver.drive(0,-127,0,0);
//
////positive across
//if (currentTime >24000 && currentTime <33000)
//  motorDriver.drive(127,0,0,127);
//
////negative across
//if (currentTime >33000 && currentTime <42000)
//  motorDriver.drive(-127,0,0,-127);
//
////positive uppity up 
//if (currentTime >42000 && currentTime <50000)
//  motorDriver.drive(0,-127,0,0);
//  
//if (currentTime > 50000)
//  motorDriver.drive(0,0,0,0);


//if (currentTime >2000 && currentTime <4000)
//  motorDriver.drive(0, 0,,0);
//  else 
//    motorDriver.drive (0,0,0,0);
///*turn on motor 1*/
//if (currentTime > 4000 && currentTime <6000)
//  motorDriver.drive(120, 0,0,0);
//  else 
//    motorDriver.drive (0,0,0,0);
// /*turn off motors for 2sec*/
//if (currentTime >6000 && currentTime <8000)
//  motorDriver.drive(0, 0,0,0);
//  else 
//    motorDriver.drive (0,0,0,0);
///*turn on motor 2*/
//if (currentTime > 8000 && currentTime <10000)
//  motorDriver.drive(0,120,0,0);
//  else 
//    motorDriver.drive (0,0,0,0);
///*turn off motors for 2sec*/
//if (currentTime >10000 && currentTime <12000)
//  motorDriver.drive(0, 0,0,0);
//  else 
//    motorDriver.drive (0,0,0,0);  
///*turn on motor 3*/
//if (currentTime > 12000 && currentTime <14000)
//  motorDriver.drive(0,0,0,120);
//  else 
//     motorDriver.drive (0,0,0,0);







  // DONT CHANGE CODE BELOW THIS LINE 
  // --------------------------------------------------------------------------
  if (printer.loopTime(loopStartTime)) {
    printer.printToSerial();  // To stop printing, just comment this line out
  }

  if (imu.loopTime(loopStartTime)) {
    imu.read(); // this is a sequence of blocking I2C read calls
    imu.printState(); // a lot of random information
  }

  // uses the LED library to flash LED -- use this as a template for new libraries!
  if (led.loopTime(loopStartTime)) {
    led.flashLED();
  }

  if (logger.loopTime(loopStartTime) && keepLogging) {
    keepLogging = logger.log();
  }
}
