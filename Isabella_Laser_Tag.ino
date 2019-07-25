                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // Daniel's condensed laser tag

// Output pins
int IR_LED = 2;
int  hit_LED= 7;

// Input pins
int IR_Sensor  = 12;
int triggerPin = 13;

int beingHit = 0;
int triggerPressed = 0;

int hp = 20;
int temp = 0;
int cooldown = 5000;
int alive = 1;
int canFire = 1;
unsigned long prevUpdate;
void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(IR_LED, OUTPUT);
  pinMode(hit_LED, OUTPUT);

  pinMode(IR_Sensor, INPUT);

  digitalWrite(triggerPin, HIGH);

  prevUpdate = millis();

  Serial.println("Ready!");
}

void loop() {
  receiveIR();

  fakeUserInput();

  updateOutputs();
}

void receiveIR() {
  beingHit = digitalRead(IR_Sensor) == HIGH;
}

void checkUserInput() {
  // TODO: get actual user input
}

// model user input as a Markov chain
// Every 250 milliseconds, make a new decision
// If we aren't firing, fire with a 10% chance
// If we are firing, stop firing with a 20% chance

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
  if (cooldown == 0) {
    temp = 5000;
    cooldown = 2000;
    canFire = 1;
  }
  if (!canFire) {
    cooldown = cooldown - 1;
  }
  digitalWrite(hit_LED, LOW);
  digitalWrite(IR_LED, LOW);
  if (beingHit == HIGH) {
    hp = hp - 1;
    digitalWrite(hit_LED, HIGH);
    if (hp == 0) {
      alive = 0;
    }
  }
  if (triggerPressed == HIGH && canFire) {
    temp = temp + 1;
    digitalWrite(IR_LED,HIGH);
      if(temp == 5000) {
        canFire = 0;
    }
   else {
    temp = max(0, temp - 1);
   }
  }
  //digitalWrite(HIT_PIN, beingHit ? HIGH : LOW);
  //digitalWrite(IR_TRANSMIT_PIN, triggerPressed ? HIGH : LOW);
}
