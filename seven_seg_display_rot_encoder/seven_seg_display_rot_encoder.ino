#define clearPin 5
#define serialData 6
#define shiftClock 7
#define latchClock 8

#define dig1 9
#define dig2 10
#define dig3 11
#define dig4 12

#define enc_a 2
#define enc_b 3

#define rotBut 13

byte lastButtonState;
unsigned long lastTimeButtonStateChanged = millis();
unsigned long debounceDuration = 50; // millis

unsigned long _lastIncReadTime = micros(); 
unsigned long _lastDecReadTime = micros(); 
int _pauseLength = 25000;
int _fastIncrement = 5;

// these integers translated into binary will send the correct signal to the SSD to form that said number
const int ZERO = 252;
const int ONE = 96;
const int TWO = 218;
const int THREE = 242;
const int FOUR = 102;
const int FIVE = 182;
const int SIX = 190;
const int SEVEN = 224;
const int EIGHT = 254;
const int NINE = 230;

volatile int counter = 0;

void setup() {
  // put your setup code here, to run once:
  byte numDigits = 4;
  byte digitPins[] = {9, 10, 11, 12};
  byte segmentPins[] = {12, 7, 1, 6, 4, 11, 8, 0};
  bool resistorsOnSegments = true;

  
  pinMode(clearPin, OUTPUT);
  pinMode(serialData, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);

  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);

  digitalWrite(clearPin, LOW);
  digitalWrite(clearPin, HIGH);

  // use inputs with pull resistors
  pinMode(enc_a, INPUT_PULLUP);
  pinMode(enc_b, INPUT_PULLUP);

  // setup interrupts to read rotary encoder input
  attachInterrupt(digitalPinToInterrupt(enc_a), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc_b), read_encoder, CHANGE);

  pinMode(rotBut, INPUT);
  lastButtonState = digitalRead(rotBut);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  static int lastCounter = 0;

  if (counter != lastCounter) {
    Serial.println(counter);
    lastCounter = counter;
  }

  //Serial.print(counter);

  if (counter < 0){ counter = 0; }
  if (counter > 255){ counter = 255; }

  static unsigned long timer = millis();

  if (millis() >= timer){
    timer += 300;
    //sevseg.setNumber(counter, -1);
  }

  //sevseg.refreshDisplay();

  // read rotary pushbutton input w/ debounce
  if (millis() - lastTimeButtonStateChanged >= debounceDuration){
    byte buttonState = digitalRead(rotBut);
    if (buttonState != lastButtonState){
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW){
        Serial.println("Button released!");

        if (counter > 0){
          counter = 0;
        } else {
          counter = 255;
        }
      }
    }
  }

  /*
  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, LSBFIRST, 0);
  shiftOut(serialData, shiftClock, LSBFIRST, THREE);
  shiftOut(serialData, shiftClock, LSBFIRST, FIVE);
  digitalWrite(latchClock, HIGH);
  

  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, LSBFIRST, 187);
  shiftOut(serialData, shiftClock, LSBFIRST, ONE);
  shiftOut(serialData, shiftClock, LSBFIRST, ONE);
  digitalWrite(latchClock, HIGH);
  */

  writeInt(counter);



    
}

void writeInt(int num){

  String numString = static_cast<String>(num);
  int digits[numString.length()] = {};
  
  //int digPins[4] = {digitOne, digitTwo, digitThree, digitFour};
  //int digPinsBckwd[4] = {digitFour, digitThree, digitTwo, digitOne};

  // create array of ints from input int (637 -> [6, 3, 7])
  for(int i = 0; i < numString.length(); i++){
    String dig = static_cast<String>(numString[i]);
    digits[i] = dig.toInt();
  }

    
  for(int i = 0; i < numString.length(); i++){
    //soleDigit(i+1);
    //ssdWrite(encodeDig(digits[i]));
    digitalWrite(latchClock, LOW);
    
    // only turn on the digit of the seven segment display corresponding to the current index in the array
    if((i+1) == 1){
      //shiftOut(serialData, shiftClock, LSBFIRST, 119);
      digitalWrite(dig1, LOW);
      digitalWrite(dig2, HIGH);
      digitalWrite(dig3, HIGH);
      digitalWrite(dig4, HIGH);
    }
    
    else if((i+1) == 2){
      //shiftOut(serialData, shiftClock, LSBFIRST, 187);
      digitalWrite(dig2, LOW);
      digitalWrite(dig1, HIGH);
      digitalWrite(dig3, HIGH);
      digitalWrite(dig4, HIGH);
    }
    
    else if((i+1)== 3){
      //shiftOut(serialData, shiftClock, LSBFIRST, 221);
      digitalWrite(dig3, LOW);
      digitalWrite(dig2, HIGH);
      digitalWrite(dig1, HIGH);
      digitalWrite(dig4, HIGH);
    }
    
    else if((i+1) == 4){
      //shiftOut(serialData, shiftClock, LSBFIRST, 238);
      digitalWrite(dig2, HIGH);
      digitalWrite(dig3, HIGH);
      digitalWrite(dig1, HIGH);
      digitalWrite(dig4, LOW);
    }

    shiftOut(serialData, shiftClock, MSBFIRST, digits[i]);
    //shiftOut(serialData, shiftClock, LSBFIRST, encodeDig(digits[i]));

    digitalWrite(latchClock, HIGH);
    
    delay(5);
    
  }

  //delay(5);
}

int encodeDig(int num){

  if (num==0){ return ZERO; }
  if (num==1){ return ONE; }
  if (num==2){ return TWO; }
  if (num==3){ return THREE; }
  if (num==4){ return FOUR; }
  if (num==5){ return FIVE; }
  if (num==6){ return SIX; }
  if (num==7){ return SEVEN; }
  if (num==8){ return EIGHT; }
  if (num==9){ return NINE; }
    
}

void soleDigit(int digit){
  digitalWrite(latchClock, LOW);

  //shiftOut(serialData, shiftClock, LSBFIRST, 0);
  //shiftOut(serialData, shiftClock, LSBFIRST, 0);

  if(digit == 1){
    shiftOut(serialData, shiftClock, LSBFIRST, 238);
  }
  
  if(digit == 2){
    shiftOut(serialData, shiftClock, LSBFIRST, 187);
  }
  
  if(digit == 3){
    shiftOut(serialData, shiftClock, LSBFIRST, 221);
  }
  
  if(digit == 4){
    shiftOut(serialData, shiftClock, LSBFIRST, 238);
  }

  digitalWrite(latchClock, HIGH);

}

void read_encoder(){

  static uint8_t old_AB = 3;  // Lookup table index
  static int8_t encval = 0;   // Encoder value  
  static const int8_t enc_states[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

  old_AB <<=2;  // Remember previous state

  if (digitalRead(enc_a)) old_AB |= 0x02; // Add current state of pin A
  if (digitalRead(enc_b)) old_AB |= 0x01; // Add current state of pin B
  
  encval += enc_states[( old_AB & 0x0f )];


  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval > 3 ) {        // Four steps forward
    int changevalue = 1;
    if((micros() - _lastIncReadTime) < _pauseLength) {
      changevalue = _fastIncrement * changevalue; 
    }
    _lastIncReadTime = micros();

    counter = counter + changevalue;              // Update counter  
    encval = 0;
  }
  
  else if( encval < -3 ) {        // Four steps backward
    int changevalue = -1;
    if((micros() - _lastDecReadTime) < _pauseLength) {
      changevalue = _fastIncrement * changevalue; 
    }
    _lastDecReadTime = micros();

    counter = counter + changevalue;              // Update counter
    encval = 0;
  }

}
