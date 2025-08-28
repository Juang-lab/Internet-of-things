const int ROJO = 13;
const int AMARILLO = 12;
const int VERDE = 11;

void setup() {
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop() {
    for (int i = 0; i < 5; i++) {
    digitalWrite(ROJO, HIGH);
    delay(300);
    digitalWrite(ROJO, LOW);
    delay(300);
  }

    for (int i = 0; i < 5; i++) {
    digitalWrite(AMARILLO, HIGH);
    delay(300);
    digitalWrite(AMARILLO, LOW);
    delay(300);
  }

  for (int i = 0; i < 5; i++) {
    digitalWrite(VERDE, HIGH);
    delay(300);
    digitalWrite(VERDE, LOW);
    delay(300);
  }
}