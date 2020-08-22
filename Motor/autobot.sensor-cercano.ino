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

int speed = 170;
int rotateSpeed = 170;
int searchDelay = 3;
int advanceDelay = 1;
int searchAngle = 100;
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
    void Drive(int speed){
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
  Serial.begin(9600);
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
  Serial.print("loop");
  bool val = digitalRead (LineFollowerSensor) ;
  Serial.println(val);
  bool course_corrected = true;
  // El valor es HIGH cuando se sale de la linea (Cuando sale de la linea se prende el LED)
  if(!val) {
    course_corrected = correct_course(val, leftMotor, rightMotor);
  }
  // move straight
  if(course_corrected) {
    leftMotor.Drive(speed);
    rightMotor.Drive(speed);
  } else {
    leftMotor.Drive(0);
    leftMotor.Drive(0);
  }
  

  delay(advanceDelay);


}

bool correct_course(bool onLine, Motor leftMotor, Motor rightMotor) {

      leftMotor.Drive(0);
      bool findLeft = searchLeft(searchAngle, rightMotor);
      if (findLeft) {
        return true;
      }
      rightMotor.Drive(0);
      bool findRight = searchRight(searchAngle, leftMotor);
      if (findRight) {
        return true;
      }
      return false;
}

bool searchLeft(int angle, Motor rightMotor) {
  bool isInline = digitalRead (LineFollowerSensor);
  int i = 0;
  rightMotor.Drive(rotateSpeed);
  Serial.println("Search Left");
  while(i < angle) {
    delay(searchDelay);
    isInline = digitalRead(LineFollowerSensor);
    if (isInline) {
      return true;
    }
    i = i + 1;
  }
  rightMotor.Drive(-1*rotateSpeed);
  Serial.println("Reverse Search Left");
  while(i > 0) {
    delay(searchDelay);
    i = i - 1;
  }
  return false;
}

bool searchRight(int angle, Motor leftMotor) {
  bool isInline = digitalRead (LineFollowerSensor) ;
  int i = 0;
  leftMotor.Drive(rotateSpeed);
  Serial.println("Search Right");
  while(i < angle) {
    delay(searchDelay);
    isInline = digitalRead(LineFollowerSensor);
    if (isInline) {
      return true;
    }
    i = i + 1;
  }
  Serial.println("Reverse Search Right");
  leftMotor.Drive(-1*rotateSpeed);
  while(i > 0) {
    delay(searchDelay);
    i = i - 1;
  }
  return false;
}
