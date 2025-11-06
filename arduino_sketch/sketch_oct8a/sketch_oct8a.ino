# define
void setup() {
pinMode(11,OUTPUD);
Serial.begin(9600);
Serial.print("Menu");
Serial.print("[1]. Turn on L1");
Serial.print("[]. Turn off L1");
Serial.print("Press only option");
}



