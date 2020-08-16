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
}


void loop() {

leftMotor.Drive(255);
rightMotor.Drive(200);

delay(2000);

leftMotor.Drive(-150);
rightMotor.Drive(-255);

delay(2000);

leftMotor.Drive(150);
rightMotor.Drive( 150);

delay(2000);
 

}
