/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#include <Servo.h>

Servo servo;  // create servo object to control a servo

int potInput = 0; // Analog in for potentiometer

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int pinServo = 3;

int potVal;
int servoVal;
int redVal = 150;
int greenVal = 150;
int blueVal = 150;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Setea el attach del servo al puerto 3
  servo.attach(3); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  potVal = analogRead(potInput);
  // print out the value you read:
  // move servo
  servoVal = map(potVal, 0, 1023, 0, 180);
  servo.write(servoVal);
  redVal = map(potVal, 0, 1023, 0, 255);
  greenVal = map(potVal, 0, 1023, 0, 255);
  blueVal = map(potVal, 0, 1023, 0, 255);
  setColor(redVal, greenVal, blueVal);
  printLimits(1043, -20);
  Serial.print(redVal);
  Serial.print(" ");
  Serial.print(greenVal);
  Serial.print(" ");
  Serial.print(blueVal);
  Serial.print(" ");
  Serial.println(potVal);
  delay(30);        // delay in between reads for stability
}

void printLimits( int top, int bottom){
  Serial.print(top);
  Serial.print(" ");
  Serial.print(bottom);
  Serial.print(" ");
}

void calcColors(int potVal) {
  redVal = map(potVal, 0, 1023, 0, 255);
  greenVal = map(potVal, 0, 1023, 0, 255);
  blueVal = map(potVal, 0, 1023, 0, 255);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
