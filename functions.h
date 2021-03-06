//Variables for functions:
unsigned int sensorValues[QTR_PIN];   //Store all the QTR-detector values in an array
unsigned int frontDistance;           //Stores the distance measured by the front-distance sensor
unsigned int rearDistance;            //For the rear-distance sensor

//Including classes and objects:
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

// Set motor at attack-speed for an amount of time:
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
    // if leftmost sensor detects line, reverse and turn to the right:
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_TIME);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_TIME);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensorValues[5] < QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left:
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_TIME);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_TIME);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}

//Start countdown when button is pressed:
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

// Function for turning 180 degrees
void flip() {
  Serial.println("Flipping");
  motors.setSpeeds(-ATTACK_SPEED, ATTACK_SPEED);
  delay(FLIP_TIME);
}
