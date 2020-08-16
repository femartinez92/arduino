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

void setup() {
  Serial.begin(9600);
    // Setup pin mode
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
  //Drive Motor Forward
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.println("Drive Motor Forward");

  delay(2000);

  //Drive Motor Backward
  analogWrite(enA, 70);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.println("Drive Motor Backward");

  delay(2000);

}
