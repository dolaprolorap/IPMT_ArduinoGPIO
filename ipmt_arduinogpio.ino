// Pins macros
#define START_PIN 2
#define PIN_COUNT 6

// Commands macros
#define UNKNOWN_COM -1

// States
#define WANT_COM 0
#define WANT_PIN 1

// Serial
#define SERIAL_BAUD 9600

void setup() {
  // Init pins
  for(int i = 0; i < PIN_COUNT; i++) {
    pinMode(START_PIN + i, OUTPUT);
  }
  Serial.begin(SERIAL_BAUD);
}

int com = UNKNOWN_COM;
int state = WANT_COM;

void loop() {
  // Waiting for the data
  if(!Serial.available()) return;
  int symb = Serial.read();
  Serial.println(symb);

  if(state == WANT_COM) {
    if(symb == 's') com = HIGH;
    else if(symb == 'c') com = LOW;
    else return;

    state = WANT_PIN;
  }
  else {
    if(symb == 's') com = HIGH;
    else if(symb == 'c') com = LOW;

    int pin = symb - '0';
    if(pin >= START_PIN && pin < START_PIN + PIN_COUNT) {
      digitalWrite(pin, com);
      com = UNKNOWN_COM;
      state = WANT_COM;
    }
  }
}
