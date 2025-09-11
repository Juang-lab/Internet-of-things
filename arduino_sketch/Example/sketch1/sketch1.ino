void setup() {
Serial.begin(9600);
Serial.println("Welcome");
menu(); 
  
}

void loop() {
if (Serial.available () > 0)
serial.print("");

  
}

void menu() {
Serial.println("Main menu");
Serial.println("1. Turn on led red");
Serial.println("2. Turn off led red");
Serial.println("3. Turn on led yellow");
Serial.println("4. Turn off led yellow");
Serial.println("5. Turn on led green");
Serial.println("6. Turn off led green");
Serial.println("7. Turn on all");
Serial.println("8. Turn off all");
Serial.println("9. Intermitence");
serial.print("Press any option ");


}