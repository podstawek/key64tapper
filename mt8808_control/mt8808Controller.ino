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
  pinMode(AX0, OUTPUT);
  pinMode(AX1, OUTPUT);
  pinMode(AX2, OUTPUT);
  pinMode(AY0, OUTPUT);
  pinMode(AY1, OUTPUT);
  pinMode(AY2, OUTPUT);
  pinMode(DAT, OUTPUT);
  pinMode(STR, OUTPUT);
  pinMode(RES, OUTPUT);

  digitalWrite(RES, HIGH);
  delay(10);
  digitalWrite(RES, LOW);

}

void strobeReset () 
{
  digitalWrite(DAT, HIGH);
  digitalWrite(STR, HIGH);
  digitalWrite(STR, LOW);
  delay(20);
  digitalWrite(RES, HIGH);
  digitalWrite(RES, LOW);
}

void strobeOnly () {
  digitalWrite(DAT, HIGH);
  digitalWrite(STR, HIGH);
  digitalWrite(STR, LOW);
  delay(20);
}

void loop() {

  delay(1000);

// AAAA działa!!
  digitalWrite(AY2, LOW);
  digitalWrite(AX2, LOW);
  digitalWrite(AX0, HIGH);
  digitalWrite(AX1, LOW);
  digitalWrite(AY0, LOW);
  digitalWrite(AY1, HIGH);
  strobeReset();


/// U działa!!!!
  digitalWrite(AY2, HIGH);
  digitalWrite(AX2, LOW);
  digitalWrite(AX0, HIGH);
  digitalWrite(AX1, HIGH);
  digitalWrite(AY0, LOW);
  digitalWrite(AY1, HIGH);
  
  strobeReset();

/// L działa!!!!!
  digitalWrite(AY2, LOW);
  digitalWrite(AX2, HIGH);
  digitalWrite(AX0, HIGH);
  digitalWrite(AX1, LOW);
  digitalWrite(AY0, LOW);
  digitalWrite(AY1, HIGH);
  
  strobeReset();


/// Shift + 6 =  &
  digitalWrite(AY2, HIGH);
  digitalWrite(AX2, LOW);
  digitalWrite(AX0, HIGH);
  digitalWrite(AX1, LOW);
  digitalWrite(AY0, HIGH);
  digitalWrite(AY1, HIGH);
  strobeOnly();
  digitalWrite(AY2, LOW);
  digitalWrite(AX2, LOW);
  digitalWrite(AX0, LOW);
  digitalWrite(AX1, HIGH);
  digitalWrite(AY0, HIGH);
  digitalWrite(AY1, HIGH);
  
  strobeReset();

}

