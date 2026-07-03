// Task 5: Beeping Countdown.
// Wiring: buzzer on pin 8; 7-seg segments a..g on pins 2,3,4,5,6,7,9 (common cathode).
// COM pin of display -> GND rail through 220 ohm resistor.

int buzzerPin = 8;
int segmentPins[] = {2, 3, 4, 5, 6, 7, 9}; // a, b, c, d, e, f, g
int numSegments = 7;

// Digit patterns: 1 = segment ON, 0 = segment OFF
byte digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

// showDigit: display digit n (0..9) on the 7-segment
void showDigit(int n) {
  if (n < 0 || n > 9) return;
  for (int i = 0; i < numSegments; i++) {
    digitalWrite(segmentPins[i], digits[n][i]);
  }
}

void setup() {
  Serial.begin(9600);

  // set up the buzzer
  pinMode(buzzerPin, OUTPUT);

  // set up each segment pin as OUTPUT and start OFF
  for (int i = 0; i < numSegments; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }

  Serial.println("=== Beeping Countdown Starting ===");

  // Count down from 9 to 1 inside setup (runs once)
  int count = 9;
  while (count >= 1) {
    Serial.print("Counting: ");
    Serial.println(count);

    showDigit(count);

    // short beep: 1000 Hz for 200 ms
    tone(buzzerPin, 1000, 200);

    // keep the digit visible for 1 second total
    delay(1000);

    count = count - 1;
  }

  // Show 0 and play longer completion tone
  showDigit(0);
  Serial.println("Counting: 0");
  // longer completion tone: 1500 Hz for 1000 ms
  tone(buzzerPin, 1500, 1000);
  delay(1000);

  Serial.println("=== Countdown Complete ===");
}

void loop() {
  // empty - everything happens once in setup()
}