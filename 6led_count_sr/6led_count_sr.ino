#define clearPin 5
#define serialData 6
#define shiftClock 7
#define latchClock 8


void setup() {
  // put your setup code here, to run once:
  pinMode(clearPin, OUTPUT);
  pinMode(serialData, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);

  digitalWrite(clearPin, LOW);
  digitalWrite(clearPin, HIGH);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 64; i++){
      digitalWrite(latchClock, LOW);
      shiftOut(serialData, shiftClock, MSBFIRST, i);
      digitalWrite(latchClock, HIGH);
      delay(500);
    }

    

}
