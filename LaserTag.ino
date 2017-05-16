// Daniel's condensed laser tag

// Output pins
int IR_TRANSMIT_PIN = 2;
int HIT_PIN         = 7;

// Input pins
int IR_RECEIVE_PIN  = 12;

int beingHit = 0;
int triggerPressed = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(IR_TRANSMIT_PIN, OUTPUT);
  pinMode(HIT_PIN, OUTPUT);

  pinMode(IR_RECEIVE_PIN, INPUT);

  digitalWrite(triggerPin, HIGH);

  prevUpdate = millis();

  Serial.println("Ready!")
}

void loop() {
  receiveIR();

  fakeUserInput();

  updateOutputs();
}

void receiveIR() {
  beingHit = digitalRead(IRreceivePin) == LOW;
}

void checkUserInput() {
  // TODO: get actual user input
}

// model user input as a Markov chain
// Every 250 milliseconds, make a new decision
// If we aren't firing, fire with a 10% chance
// If we are firing, stop firing with a 20% chance
unsigned long prevUpdate;
int PERIOD = 250;
void fakeUserInput() {
  unsigned long currentTime = millis();
  while (prevUpdate + PERIOD < currentTime) {
    prevUpdate += PERIOD;
    if (triggerPressed) {
      triggerPressed = random(5);
    } else {
      triggerPressed = !random(10);
    }
  }
}

void updateOutputs() {
  digitalWrite(HIT_PIN, beingHit ? HIGH : LOW);
  digitalWrite(IR_TRANSMIT_PIN, triggerPressed ? HGIH : LOW);
}

