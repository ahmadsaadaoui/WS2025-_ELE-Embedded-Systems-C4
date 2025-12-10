const int RedPin = 13;
const int YellowPin = 10;
const int GreenPin = 2;

const int RedPedestrian = 6;
const int GreenPedestrian = 7;
const int Button = 9;

// ================== Timing ==================
const unsigned long TrafficTime = 2500;
const unsigned long YellowTime = 1000;
const unsigned long PedestrianCrossTime = 4000;

// ================== State Machine ==================
enum TrafficState { RED, YELLOW_AFTER_RED, GREEN, YELLOW_AFTER_GREEN };
TrafficState state = RED;

bool pedestrianRequest = false;

// ================== Setup ==================
void setup() {
  pinMode(RedPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPedestrian, OUTPUT);
  pinMode(GreenPedestrian, OUTPUT);
  pinMode(Button, INPUT_PULLUP);

  setTrafficLights(true, false, false);
  setPedestrianLights(false, true); // Pedestrian green when starting on RED
}

// ================== Loop ==================
void loop() {
  checkPedestrianButton(); 

  switch (state) {
    case RED: handleRedState(); break;
    case YELLOW_AFTER_RED: handleYellowAfterRedState(); break;
    case GREEN: handleGreenState(); break;
    case YELLOW_AFTER_GREEN: handleYellowAfterGreenState(); break;
  }
}

// ================== Functions ==================
void setTrafficLights(bool red, bool yellow, bool green) {
  digitalWrite(RedPin, red);
  digitalWrite(YellowPin, yellow);
  digitalWrite(GreenPin, green);
}

void setPedestrianLights(bool red, bool green) {
  digitalWrite(RedPedestrian, red);
  digitalWrite(GreenPedestrian, green);
}

void checkPedestrianButton() {
  if (digitalRead(Button) == LOW) {
    pedestrianRequest = true;
  }
}

void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    checkPedestrianButton();
  }
}

void handleRedState() {
  setTrafficLights(true, false, false);
  setPedestrianLights(false, true);   // ? Pedestrian always green in RED phase

  // If a pedestrian pressed the button earlier, extend crossing time
  if (pedestrianRequest) {
    smartDelay(PedestrianCrossTime);
    pedestrianRequest = false;
  }

  smartDelay(TrafficTime);
  state = YELLOW_AFTER_RED;
}

void handleYellowAfterRedState() {
  setTrafficLights(false, true, false);
  setPedestrianLights(true, false); // Pedestrian red
  smartDelay(YellowTime);
  state = GREEN;
}

void handleGreenState() {
  setTrafficLights(false, false, true);
  setPedestrianLights(true, false); // Pedestrian red
  smartDelay(TrafficTime);
  state = YELLOW_AFTER_GREEN;
}

void handleYellowAfterGreenState() {
  setTrafficLights(false, true, false);
  setPedestrianLights(true, false); // Pedestrian red
  smartDelay(YellowTime);
  state = RED;
}


