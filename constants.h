const int LED = 13;
const int F_DIST_PIN = A0;                     //Trigger pin for the distance sensor mounted on top of the robot
const int QTR_PIN = 6;                       //Pin for QTR-sensor, for edge detection
const int TRIG_PIN = 11;           			 //connects to the trigger pin on the rear-distance sensor       
const int ECHO_PIN = 12;           			 //connects to the echo pin on the rear-distance sensor   

const byte MEDIAN_FILTER_WINDOW_SIZE = 5;    //Window size of the median filter (odd number, 1 = no filtering)

//Threshold:
const int QTR_THRESHOLD = 1500;           //microseconds (default value @1500)
const int ATTACK_RANGE = 300;             //threshold for IR sensor, this determines how close the oppnent must be for an attack

// Speed configurations:
const int REVERSE_SPEED = 200;  // (0 is stopped, 400 is full speed)
const int TURN_SPEED = 200;
const int FORWARD_SPEED = 200;
const int ATTACK_SPEED = 400;

// Time configurations:
const int REVERSE_TIME = 200; //ms
const int TURN_TIME = 400;    //ms
const int ATTACK_TIME = 75;  //ms
