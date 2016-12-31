/*
  Reading a serial ASCII-encoded string.

 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.

 Circuit: Common-Cathode RGB LED wired like so:
 * Red anode: digital pin 3
 * Green anode: digital pin 5
 * Blue anode: digital pin 6
 * Cathode : GND

 created 13 Apr 2012
 by Tom Igoe
 
 modified 14 Mar 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 */

const int AX0 = 31;      // Pins 5-10 assigned to
const int AX1 = 33;      // address lines AX0-AX2
const int AX2 = 35;      // and AY0-AY2
const int AY0 = 37;
const int AY1 = 39;
const int AY2 = 41;

const int DAT = 43;   // Data
const int STR = 45;   // Strobe
const int RES = 47;   // Reset


void setup() {
  // initialize serial:
  Serial.begin(9600);


}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int in0 = Serial.parseInt();
    int in1 = Serial.parseInt();
    int in2 = Serial.parseInt();
    int in3 = Serial.parseInt();
    int in4 = Serial.parseInt();
    int in5 = Serial.parseInt();
    

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {

      if (in0 == 1) {
        digitalWrite(AY2, HIGH);
      } else {
        digitalWrite(AY2, LOW);
      }

      if (in1 == 1) {
        digitalWrite(AY1, HIGH);
      } else {
        digitalWrite(AY1, LOW);
      }

      if (in2 == 1) {
        digitalWrite(AY0, HIGH);
      } else {
        digitalWrite(AY0, LOW);
      }

      if (in3 == 1) {
        digitalWrite(AX2, HIGH);
      } else {
        digitalWrite(AX2, LOW);
      }


      if (in4 == 1) {
        digitalWrite(AX1, HIGH);
      } else {
        digitalWrite(AX1, LOW);
      }


      if (in5 == 1) {
        digitalWrite(AX0, HIGH);
      } else {
        digitalWrite(AX0, LOW);
      }

      // print the three numbers in one string as hexadecimal:
      Serial.print(in0, HEX);
      Serial.print(in1, HEX);
      Serial.print(in2, HEX);
      Serial.print(in3, HEX);
      Serial.print(in4, HEX);
      Serial.println(in5, HEX);
    }
  }
}
