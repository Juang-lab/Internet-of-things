// Pines del sensor y LEDs
int trigPin = 7;
int echoPin = 6;
int ledVerde = 4;
int ledAmarillo = 3;
int ledRojo = 2;

// Variables de distancia
long distancia;
long duracion;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  
  Serial.println("Sistema de deteccion de agua iniciado");
}

void loop() {
  // Medir distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2; // Convertir a cm
  
  // Mostrar distancia
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  // Controlar LEDs según distancia
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);
  
  if (distancia > 150) {
    // Agua lejos - LED verde
    digitalWrite(ledVerde, HIGH);
    Serial.println("Estado: NORMAL");
  }
  else if (distancia > 100) {
    // Distancia media - LED amarillo
    digitalWrite(ledAmarillo, HIGH);
    Serial.println("Estado: ATENCION");
  }
  else if (distancia > 50) {
    // Agua cerca - LED rojo
    digitalWrite(ledRojo, HIGH);
    Serial.println("Estado: PELIGRO");
  }
  else {
    // Agua muy cerca - LED rojo parpadeante
    digitalWrite(ledRojo, HIGH);
    delay(250);
    digitalWrite(ledRojo, LOW);
    delay(250);
    Serial.println("Estado: CRITICO!");
  }
  
  delay(100);
}