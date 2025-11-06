
#include<DHT.h>
#define DHTPIN 10
#define DHTTYPE DHT11
#define LED_RED 13
float humidity, temperature;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  Serial.print(":: Hello to Weather Station ::");
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if(isnan(humidity) || isnan(temperature)){
    Serial.print("Error reading sensor.");
    return;
  }
  
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(temperature);
  /*
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  */
  delay(2000);

  //NaN: Not a Number
}