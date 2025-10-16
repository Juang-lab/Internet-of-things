#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;  
const int ledPin = 13;       
const int motorPin = 9; 

float temperatura = 0;

void setup() {
  lcd.begin(16, 2);         
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void loop() {
  int lectura = analogRead(sensorPin);
  float voltaje = lectura * (5.0 / 1023.0);
  temperatura = (voltaje - 0.5) * 100.0;  

  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print((char)223); 
  lcd.print("C   ");

 
  if (temperatura <= 10) {
   
    digitalWrite(motorPin, LOW);

   
    lcd.setCursor(0, 1);
    lcd.print("FRIO: LED Blink ");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);

  } else if (temperatura > 10 && temperatura <= 25) {
    
    digitalWrite(ledPin, LOW);
    digitalWrite(motorPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("NORMAL          ");
    delay(1000);

  } else if (temperatura >= 26) {
    
    digitalWrite(ledPin, HIGH);
    digitalWrite(motorPin, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("CALOR: Motor ON ");
    delay(1000);
  }
}