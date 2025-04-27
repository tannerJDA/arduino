// Define the LED pins
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;

// number of LEDs
const int numLeds = 4;

// counter
int count = 0;

void setup() {
  // Set the LED pins as output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPin1 + i, OUTPUT);
  }
}

void loop() {
  // Increment the counter
  count++;

  // Check if the counter has exceeded the maximum value (15 for 4 LEDs)
  if (count > 15) {
    count = 0; // Reset the counter
  }

  // Display the binary number on the LEDs
  for (int i = 0; i < numLeds; i++) {
    if (bitRead(count, i) == 1) {
      digitalWrite(ledPin1 + i, HIGH); // Turn LED on
    } else {
      digitalWrite(ledPin1 + i, LOW);  // Turn LED off
    }
  }

  delay(500); // Delay to see the LED pattern
}
