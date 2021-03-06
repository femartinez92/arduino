/*  Arduino DC Motor L298N Module H-bridge DC Motor
    By Chen The Design Maker  chenthedesignmaker.com
*/

//Define all the connections maps to the L298N
#define enA 10
#define in1 9
#define in2 8

#define in3 7
#define in4 6
#define enB 5

class Motor{

    int enablePin;
    int directionPin1;
    int directionPin2;
    public:
    
    //Method to define the motor pins
    Motor(int ENPin,int dPin1,int dPin2){
      enablePin = ENPin;
      directionPin1 = dPin1;
      directionPin2 = dPin2;
    };     
    
    //Method to drive the motor 0~255 driving forward. -1~-255 driving backward
    Drive(int speed){
    if(speed>=0){
        digitalWrite(directionPin1, LOW);
        digitalWrite(directionPin2, HIGH);
      }
    else{
        digitalWrite(directionPin1, HIGH);
        digitalWrite(directionPin2, LOW);
        speed = - speed;
      } 
    analogWrite(enablePin, speed);  
    }
  };

Motor leftMotor = Motor(enA, in1, in2);
Motor rightMotor = Motor(enB, in3, in4);
#define LineFollowerSensor 3 // Declaration of the sensor input pin
  
void setup() {
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
  //
  pinMode (LineFollowerSensor, INPUT) ;
}


void loop() {

  bool val = digitalRead (LineFollowerSensor) ;
  bool course_corrected = true;
  // El valor es HIGH cuando se sale de la linea (Cuando sale de la linea se prende el LED)
  if(val == HIGH) {
    course_corrected = correct_course(val == HIGH, leftMotor, rightMotor);
  }
  // move straight
  if(course_corrected) {
    leftMotor.Drive(70);
    rightMotor.Drive(70);
  } else {
    leftMotor.Drive(0);
    leftMotor.Drive(0);
  }
  

  delay(200);


}

bool correct_course(bool onLine, Motor leftMotor, Motor rightMotor) {

      leftMotor.Drive(0);
      bool findLeft = searchLeft(90, rightMotor);
      if (findLeft) {
        return true;
      }
      rightMotor.Drive(0);
      bool findRight = searchRight(90, leftMotor);
      if (findRight) {
        return true;
      }
      return false;
}

bool searchLeft(int angle, Motor rightMotor) {
  bool valLeft = digitalRead (LineFollowerSensor) ;
  int i = 0;
  rightMotor.Drive(70);
  while(i < angle) {
    delay(100);
    valLeft = digitalRead(LineFollowerSensor);
    if (valLeft != HIGH) {
      return true;
    }
    i = i + 1;
  }
  rightMotor.Drive(-70);
  while(i > 0) {
    delay(100);
    i = i - 1;
  }
  return false;
}

bool searchRight(int angle, Motor leftMotor) {
  bool valRight = digitalRead (LineFollowerSensor) ;
  int i = 0;
  leftMotor.Drive(70);
  while(i < angle) {
    delay(100);
    valRight = digitalRead(LineFollowerSensor);
    if (valRight != HIGH) {
      return true;
    }
    i = i + 1;
  }
  leftMotor.Drive(-70);
  while(i > 0) {
    delay(100);
    i = i - 1;
  }
  return false;
}
