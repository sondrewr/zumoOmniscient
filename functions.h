//Variables for functions:
unsigned int sensorValues[QTR_PIN];   //Store all the QTR-detector values in an array
unsigned int frontDistance;           //Stores the distance measured by the front-distance sensor
unsigned int rearDistance = 100;            //For the rear-distance sensor

//Including classes:
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
SharpDistSensor frontDistSensor(F_DIST_PIN, MEDIAN_FILTER_WINDOW_SIZE);

// Start driving:
void goForward() {
  motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

//Return if border is detected
bool borderDetect() {
  if ((sensorValues[0] < QTR_THRESHOLD) or (sensorValues[5] < QTR_THRESHOLD)) {
    return true;
  }
  else {
    return false;
  }
}

// Set motor at attack speed for an amount of time:
void attack(int time) {
  Serial.println("Attacking");
  motors.setSpeeds(ATTACK_SPEED, ATTACK_SPEED);
  delay(time);
}

//Avoiding the edge when detected:
void borderAvoid() {
  Serial.println("Avoiding border");
    if (sensorValues[0] < QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_TIME);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_TIME);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensorValues[5] < QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_TIME);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_TIME);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}

//Waiting for button to be pressed and starting countdown:
void pressButtonToStartCountDown()
{
  //play audible starttune
  for (int i = 0; i < 10; i++)
  {
    delay(100);
    buzzer.playNote(NOTE_G(i), 100, 15); 
  }
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
  
  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15); 
  }
  
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}

//Returns the distance measuerd by the HC-SR04 rear-distance sensor
float getRearDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);

  echoTime = pulseIn(ECHO_PIN, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  
  return calculatedDistance;              //send back the distance that was calculated
}

void flip() {
    motors.setSpeeds(-ATTACK_SPEED, ATTACK_SPEED);
    delay(400);
}
