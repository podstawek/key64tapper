// Pins assigned to address lines AX0-AX2 and AY0-AY2
const int AX0 = 31; const int AX1 = 33; const int AX2 = 35;
const int AY0 = 37; const int AY1 = 39; const int AY2 = 41;

const int DAT = 43;   // Data
const int STR = 45;   // Strobe
const int RES = 47;   // Reset
const int RTR = 49;   // Restore

void setup() {
  pinMode(AX0, OUTPUT); pinMode(AX1, OUTPUT); pinMode(AX2, OUTPUT);
  pinMode(AY0, OUTPUT); pinMode(AY1, OUTPUT); pinMode(AY2, OUTPUT);
  pinMode(DAT, OUTPUT); pinMode(STR, OUTPUT); pinMode(RES, OUTPUT);
  pinMode(RTR, OUTPUT);
  digitalWrite(RTR, LOW);  // Restore key off by default

  digitalWrite(RES, HIGH); // First reset the crosspoint switch
  delay(20);
  digitalWrite(RES, LOW);

  Serial.begin(19200);     // Initialize serial port
}

void strobeReset () {
  digitalWrite(DAT, HIGH);
  digitalWrite(STR, HIGH);
  delay(10);
  digitalWrite(STR, LOW);
  delay(10);
  digitalWrite(RES, HIGH);
  digitalWrite(RES, LOW);
}

void strobeOnly () {
  digitalWrite(DAT, HIGH);
  digitalWrite(STR, HIGH);
  digitalWrite(STR, LOW);
}

void resetOnly () {
  digitalWrite(RES, HIGH);
  delay(20);
  digitalWrite(RES, LOW);
}

void diagFeedback (int in0, int in1, int in2, int in3, int in4, int in5) {
  Serial.println();
  Serial.print("Received series: ");
  Serial.print(in0); Serial.print(in1); Serial.print(in2);
  Serial.print(in3); Serial.print(in4); Serial.print(in5);
  Serial.println();
}

void sendAddress (int in0, int in1, int in2, int in3, int in4, int in5) {
  if (in0 == 1) digitalWrite(AY2, HIGH); else digitalWrite(AY2, LOW);
  if (in1 == 1) digitalWrite(AY1, HIGH); else digitalWrite(AY1, LOW);
  if (in2 == 1) digitalWrite(AY0, HIGH); else digitalWrite(AY0, LOW);
  if (in3 == 1) digitalWrite(AX2, HIGH); else digitalWrite(AX2, LOW);
  if (in4 == 1) digitalWrite(AX1, HIGH); else digitalWrite(AX1, LOW);
  if (in5 == 1) digitalWrite(AX0, HIGH); else digitalWrite(AX0, LOW);
}

void loop() {

  resetOnly(); // This zeroes out any switches which might be accidentally on/off due to garbage data

  while (Serial.available() > 0) {
    delay(10); // This is to compensate for C64 keyboard matrix scanning delay

    int r = Serial.parseInt(); // The first bit is for Restore key
    int in0 = Serial.parseInt(); int in1 = Serial.parseInt(); int in2 = Serial.parseInt();
    int in3 = Serial.parseInt(); int in4 = Serial.parseInt(); int in5 = Serial.parseInt();

    //         Uncomment the line below to get feedback to computer for diagnostic purposes
    //         diagFeedback(in0, in1, in2, in3, in4, in5);

    //    if (r == 1) digitalWrite(RTR, HIGH); else digitalWrite(RTR, LOW);

    if (Serial.read() == '\n') {

      // A single key press, or the last key of key combination
      sendAddress(in0, in1, in2, in3, in4, in5);
      strobeReset();
    } else if (Serial.read() == '_') {
      // Combination of keys, we are expecting another key now
      sendAddress(in0, in1, in2, in3, in4, in5);
      strobeOnly();
    }
  }
}



