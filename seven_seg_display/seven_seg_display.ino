#define clearPin 5
#define serialData 6
#define shiftClock 7
#define latchClock 8

#define dig1 9
#define dig2 10
#define dig3 11
#define dig4 12

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

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  writeInt(1337);

    
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
