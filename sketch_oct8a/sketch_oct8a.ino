#include <DHT.h>

#define DHTPIN 10
#define DHTTYPE DHT11
#define LED_RED 13  

DHT dht(DHTPIN, DHTTYPE);
float Humidity, Temperature;

void setup() {
  pinMode(LED_RED, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  Serial.print("Hello to weather station");
}

void loop() {
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(Humidity);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.println(Temperature);
  Serial.println("°C");

  delay(2000);
}