int RedPin = 13;
int YellowPin = 10;
int GreenPin = 2;
int t1=2500;
int t2=1000;
int state = 0;  
// Traffic light state: 0=Red, 1=Green, 2=Yellow 3=Yellow switch

void setup() {
  pinMode(RedPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
}

void loop() {
  switch (state) {
    case 0: // Red Light
      digitalWrite(RedPin, HIGH);
      digitalWrite(GreenPin, LOW);
      digitalWrite(YellowPin, LOW);
      delay(t1);
      // Red ON for 2.5 sec
      state = 2;      // Next: Green
      break;

    case 1: // Green Light
      digitalWrite(GreenPin, HIGH);
      digitalWrite(RedPin, LOW);
      digitalWrite(YellowPin, LOW);
      delay(t1);
          // Green ON for 2.5 sec
      state = 3;    // Next: Yellow
      break;

    
    case 2: // Yellow after Red
      digitalWrite(YellowPin, HIGH);
      digitalWrite(RedPin, LOW);
      digitalWrite(GreenPin, LOW);
      delay(t2);            // Yellow ON for 1 second
      state = 1;              // Next state: Green
      break;
      
    case 3: // Yellow after Green → prepares to go back to Red
      digitalWrite(YellowPin, HIGH);
      digitalWrite(RedPin, LOW);
      digitalWrite(GreenPin, LOW);
      delay(t2);            // Yellow ON for 1 second
      state = 0;              // Next state: Red
      // This case is necessary to **distinguish Yellow after Green** from Yellow after Red
      // Without case 3, the yellow light would incorrectly go to Green instead of Red
      break;
  }
}
