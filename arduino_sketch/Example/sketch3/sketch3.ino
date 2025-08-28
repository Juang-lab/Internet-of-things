const int ROJO = 13;
const int AMARILLO = 12;
const int VERDE = 11;

void setup() {
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop() {
  digitalWrite(VERDE, HIGH);
  delay(3000);
  digitalWrite(VERDE, LOW);

  digitalWrite(AMARILLO, HIGH);
  delay(1000);
  digitalWrite(AMARILLO, LOW);

  digitalWrite(ROJO, HIGH);
  delay(3000);
  digitalWrite(ROJO, LOW);
}