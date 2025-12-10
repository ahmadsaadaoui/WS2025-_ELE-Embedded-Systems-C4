// =============== ARDUINO A (Traffic Light System) ==================

// LED pins
const int redPin = 13;
const int yellowPin = 12;
const int greenPin = 11;

// Push button request FROM B
const int requestPin = 4;

// Output TO B (traffic red signal)
const int pedRedSignal = 5;

// Timing (milliseconds)
const unsigned long greenTime = 4000;
const unsigned long yellowTime = 2000;
const unsigned long redTime = 4000;

bool requestPending = false;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(requestPin, INPUT);
  pinMode(pedRedSignal, OUTPUT);

  // Start with green traffic
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(pedRedSignal, LOW); // pedestrian red
}

void loop() {
  // Read button request
  if (digitalRead(requestPin) == HIGH) {
    requestPending = true;
  }

  // ----- GREEN -----
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(pedRedSignal, LOW); // pedestrian must be red
  delay(greenTime);

  // ----- YELLOW -----
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  digitalWrite(pedRedSignal, LOW); // pedestrian still red
  delay(yellowTime);

  // ----- RED -----
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  digitalWrite(pedRedSignal, HIGH); // signal B that traffic is red

  // RED duration depends on request
  if (requestPending) {
    delay(redTime); // extend red if button pressed
    requestPending = false;
  } else {
    delay(redTime); // normal red
  }

  // ----- YELLOW AFTER RED (preparing for green) -----
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(pedRedSignal, LOW); // pedestrian red
  delay(yellowTime);
}
