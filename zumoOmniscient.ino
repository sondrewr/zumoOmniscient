#include <Wire.h>         // Include needed libraries
#include <ZumoShield.h>
#include <SharpDistSensor.h>
#include "constants.h"    // Header file containing all constants and thresholds
#include "functions.h"    // Header file containing all functions and necessary variables

void setup() {
  Serial.begin(9600);
  pinMode(LED, HIGH);
  pinMode(F_DIST_PIN, INPUT);
  pinMode(QTR_PIN, INPUT);

  pressButtonToStartCountDown();
}

void loop() {
  sensors.read(sensorValues);
  frontDistance = frontDistSensor.getDist();  //Get frontDistance from sensor values
  
  Serial.write("frontDistance = ");      //Print frontDistance to Serial for monitoring
  Serial.print(frontDistance);
  Serial.write("rearDistance = ");
  Serial.print(rearDistance);
  Serial.write(" Border = ");
  Serial.print(borderDetect());
  Serial.println(" ");

  goForward();        //In this tactic the robot starts with driving straight forward

  if (borderDetect()) {
    borderAvoid();
  }
  else if (frontDistance < ATTACK_RANGE) {
    attack(ATTACK_TIME);
  }
  else if (getRearDistance()) {
    flip();
  }
}
