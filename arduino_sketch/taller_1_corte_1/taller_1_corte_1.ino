const int BTN_PIN = 2;
const int LED_RED = 11;
const int LED_YEL = 12;
const int LED_GRN = 13;

const unsigned long DEBOUNCE_DELAY = 50;
const unsigned long BLINK_INTERVAL  = 300;

int lastRawButton = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;

enum Mode {
  MODE_MANUAL,
  MODE_RED_ONLY,
  MODE_GREEN_ONLY,
  MODE_YELLOW_ONLY,
  MODE_ALL_OFF,
  MODE_ALL_ON,
  MODE_BLINK
};

const int NUM_CYCLE_MODES = 6;
int modeIndex = 0;
Mode currentMode = MODE_MANUAL;

bool ledRedState = false;
bool ledYelState = false;
bool ledGrnState = false;

unsigned long lastBlinkMillis = 0;
bool blinkOn = false;

bool redFixedOn = false;
bool yelFixedOn = false;
bool grnFixedOn = false;

bool redFixedOff = false;
bool yelFixedOff = false;
bool grnFixedOff = false;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YEL, OUTPUT);
  pinMode(LED_GRN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Welcome");
  Serial.println("Press any key to show menu...");
  setAllOff();
}

void loop() {
  handleButtonCycle();
  handleSerial();
  applyMode();
}

void handleButtonCycle() {
  int raw = digitalRead(BTN_PIN);
  if (raw != lastRawButton) {
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
    if (raw != buttonState) {
      buttonState = raw;
      if (buttonState == LOW) {
        modeIndex = (modeIndex + 1) % NUM_CYCLE_MODES;
        switch (modeIndex) {
          case 0: currentMode = MODE_RED_ONLY;    Serial.println("Button -> MODE_RED_ONLY");    break;
          case 1: currentMode = MODE_GREEN_ONLY;  Serial.println("Button -> MODE_GREEN_ONLY");  break;
          case 2: currentMode = MODE_YELLOW_ONLY; Serial.println("Button -> MODE_YELLOW_ONLY"); break;
          case 3: currentMode = MODE_ALL_OFF;     Serial.println("Button -> MODE_ALL_OFF");     break;
          case 4: currentMode = MODE_ALL_ON;      Serial.println("Button -> MODE_ALL_ON");      break;
          case 5: currentMode = MODE_BLINK;       
                  Serial.println("Button -> MODE_BLINK"); 
                  redFixedOn = yelFixedOn = grnFixedOn = false;
                  redFixedOff = yelFixedOff = grnFixedOff = false;
                  break;
        }
        lastBlinkMillis = millis();
        blinkOn = false;
      }
    }
  }
  lastRawButton = raw;
}

void handleSerial() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\r' || c == '\n') return;
    menu();
    switch (c) {
      case '1':
        if (currentMode == MODE_BLINK) {
          redFixedOn = true; redFixedOff = false;
          Serial.println("Serial: RED FIXED ON while BLINKING");
        } else {
          currentMode = MODE_RED_ONLY;
          modeIndex = 0;
          Serial.println("Serial: RED ONLY");
        }
        break;
      case '2':
        if (currentMode == MODE_BLINK) {
          redFixedOff = true; redFixedOn = false;
          Serial.println("Serial: RED FIXED OFF while BLINKING");
        } else {
          ledRedState = false;
          currentMode = MODE_MANUAL;
          Serial.println("Serial: RED OFF (manual)");
        }
        break;
      case '3':
        if (currentMode == MODE_BLINK) {
          yelFixedOn = true; yelFixedOff = false;
          Serial.println("Serial: YELLOW FIXED ON while BLINKING");
        } else {
          currentMode = MODE_YELLOW_ONLY;
          modeIndex = 2;
          Serial.println("Serial: YELLOW ONLY");
        }
        break;
      case '4':
        if (currentMode == MODE_BLINK) {
          yelFixedOff = true; yelFixedOn = false;
          Serial.println("Serial: YELLOW FIXED OFF while BLINKING");
        } else {
          ledYelState = false;
          currentMode = MODE_MANUAL;
          Serial.println("Serial: YELLOW OFF (manual)");
        }
        break;
      case '5':
        if (currentMode == MODE_BLINK) {
          grnFixedOn = true; grnFixedOff = false;
          Serial.println("Serial: GREEN FIXED ON while BLINKING");
        } else {
          currentMode = MODE_GREEN_ONLY;
          modeIndex = 1;
          Serial.println("Serial: GREEN ONLY");
        }
        break;
      case '6':
        if (currentMode == MODE_BLINK) {
          grnFixedOff = true; grnFixedOn = false;
          Serial.println("Serial: GREEN FIXED OFF while BLINKING");
        } else {
          ledGrnState = false;
          currentMode = MODE_MANUAL;
          Serial.println("Serial: GREEN OFF (manual)");
        }
        break;
      case '7':
        setAllOn();
        currentMode = MODE_ALL_ON;
        modeIndex = 4;
        Serial.println("Serial: ALL ON");
        break;
      case '8':
        setAllOff();
        currentMode = MODE_ALL_OFF;
        modeIndex = 3;
        Serial.println("Serial: ALL OFF");
        break;
      case '9':
        currentMode = MODE_BLINK;
        modeIndex = 5;
        lastBlinkMillis = millis();
        blinkOn = false;
        redFixedOn = yelFixedOn = grnFixedOn = false;
        redFixedOff = yelFixedOff = grnFixedOff = false;
        Serial.println("Serial: BLINK MODE");
        break;
      default:
        Serial.print("Unknown option: "); Serial.println(c);
    }
  }
}

void applyMode() {
  switch (currentMode) {
    case MODE_MANUAL:
      digitalWrite(LED_RED,  ledRedState ? HIGH : LOW);
      digitalWrite(LED_YEL,  ledYelState ? HIGH : LOW);
      digitalWrite(LED_GRN,  ledGrnState ? HIGH : LOW);
      break;
    case MODE_RED_ONLY:
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YEL, LOW);
      digitalWrite(LED_GRN, LOW);
      break;
    case MODE_GREEN_ONLY:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YEL, LOW);
      digitalWrite(LED_GRN, HIGH);
      break;
    case MODE_YELLOW_ONLY:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YEL, HIGH);
      digitalWrite(LED_GRN, LOW);
      break;
    case MODE_ALL_OFF:
      setAllOff();
      break;
    case MODE_ALL_ON:
      setAllOn();
      break;
    case MODE_BLINK:
      if (millis() - lastBlinkMillis >= BLINK_INTERVAL) {
        lastBlinkMillis = millis();
        blinkOn = !blinkOn;
        if (redFixedOn) digitalWrite(LED_RED, HIGH);
        else if (redFixedOff) digitalWrite(LED_RED, LOW);
        else digitalWrite(LED_RED, blinkOn ? HIGH : LOW);
        if (yelFixedOn) digitalWrite(LED_YEL, HIGH);
        else if (yelFixedOff) digitalWrite(LED_YEL, LOW);
        else digitalWrite(LED_YEL, blinkOn ? HIGH : LOW);
        if (grnFixedOn) digitalWrite(LED_GRN, HIGH);
        else if (grnFixedOff) digitalWrite(LED_GRN, LOW);
        else digitalWrite(LED_GRN, blinkOn ? HIGH : LOW);
      }
      break;
  }
}

void setAllOff() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YEL, LOW);
  digitalWrite(LED_GRN, LOW);
  ledRedState = ledYelState = ledGrnState = false;
}

void setAllOn() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YEL, HIGH);
  digitalWrite(LED_GRN, HIGH);
  ledRedState = ledYelState = ledGrnState = true;
}

void menu() {
  Serial.println("\nMain menu");
  Serial.println("1. Turn on led red (or fix red on in blink)");
  Serial.println("2. Turn off led red (or fix red off in blink)");
  Serial.println("3. Turn on led yellow (or fix yellow on in blink)");
  Serial.println("4. Turn off led yellow (or fix yellow off in blink)");
  Serial.println("5. Turn on led green (or fix green on in blink)");
  Serial.println("6. Turn off led green (or fix green off in blink)");
  Serial.println("7. Turn on all");
  Serial.println("8. Turn off all");
  Serial.println("9. Intermitence");
  Serial.print("Press any option: ");
}

