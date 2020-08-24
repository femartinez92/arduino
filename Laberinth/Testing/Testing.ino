// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h>

// Define connections to HC-SR04
#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Define connection to SG90
#define SERVO_PIN 11 // PMW pin tied to control servo.

//Define all the connections maps to the L298N
#define enA 10
#define in1 9
#define in2 8

#define in3 7
#define in4 6
#define enB 5

int minDist = 10;
int loopDelay = 50;
int SearchDelay = 1000;
int TurnDelay = 250;
int ReturnDelay = 500;

int speed = 255;
int rotateSpeed = 170;


class Motor
  {
  int enablePin;
  int directionPin1;
  int directionPin2;
  public:
    
  //Method to define the motor pins
  Motor(int ENPin,int dPin1,int dPin2)
    {
    enablePin = ENPin;
    directionPin1 = dPin1;
    directionPin2 = dPin2;
    };     
    
    //Method to drive the motor 0~255 driving forward. -1~-255 driving backward
    void Drive(int speed)
      {
      if(speed>=0)
        {
        digitalWrite(directionPin1, LOW);
        digitalWrite(directionPin2, HIGH);
        }
      else
        {
        digitalWrite(directionPin1, HIGH);
        digitalWrite(directionPin2, LOW);
        speed = - speed;
        } 
      analogWrite(enablePin, speed);  
    }
  };


Servo servoMotor;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int searchright() {
  
  servoMotor.write(0);
  delay(SearchDelay); 
  int SearchRight = sonar.ping_cm();
  servoMotor.write(90);
  return SearchRight;
  }

  int searchleft() {
    
  servoMotor.write(180);
  delay(SearchDelay); 
  int SearchLeft = sonar.ping_cm();
  servoMotor.write(90);
  return SearchLeft;
  }

Motor leftMotor = Motor(enA, in1, in2);
Motor rightMotor = Motor(enB, in3, in4);

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Set initial direction and speed
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(90);
}

void loop() {
  
  delay(loopDelay);

  if(sonar.ping_cm() <= minDist && sonar.ping_cm() != 0)
  {
      leftMotor.Drive(0);
      rightMotor.Drive(0);
      int thissearchright = searchright();
      int thissearchleft = searchleft();
      
      if(thissearchright > 10 && thissearchright > thissearchleft)
      {
        Serial.println("Drive Right");
        leftMotor.Drive(speed);
        rightMotor.Drive(- speed);
        delay(TurnDelay);
        
      }
      else if(thissearchleft > 10 && thissearchleft > thissearchright) 
      {
        Serial.println("Drive Left");
        leftMotor.Drive(- speed);
        rightMotor.Drive(speed);
        delay(TurnDelay);
      }
      else
      {
        Serial.println("Return");
        leftMotor.Drive(speed);
        rightMotor.Drive(- speed);
        delay(ReturnDelay);
      }
  }
  else
  {
      Serial.println("Drive");
      leftMotor.Drive(speed);
      rightMotor.Drive(speed);
  }
  
}
