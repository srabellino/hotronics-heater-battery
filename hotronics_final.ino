#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;
const int pwmPin = 9;
volatile int mode = 0;
volatile int oldMode = 0;
unsigned long lastPressTime = 0;
unsigned long displayOffTime = 0;
bool displayOn = true;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeMode, FALLING);
  if (!display.begin(0x3C, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if initialization fails
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Lets get  toasty");
  display.display();
  lastPressTime = millis();
  Serial.println("Setup complete. Starting in 'Off' mode.");
}

void loop() {
  // turn off display after 5 seconds
  if (millis() - lastPressTime > 5000 && displayOn) {
    display.clearDisplay();
    display.display();
    displayOn = false;
    Serial.println("Display turned off to save battery.");
  }
  // update pwm and display with mode change
  if (oldMode !=  mode) {
    Serial.print("Button pressed. Mode changed to: ");
    Serial.println(mode);
    updateDisplay();
    updatePWM();
    // stop the number from getting too big
    if (mode > 4) {
      mode = 0;
    }
    oldMode = mode;
  }
}

void changeMode() {
  if (millis() - lastPressTime > 300) { // Debounce
    mode = (mode + 1) % 4;
    lastPressTime = millis();
    displayOn = true;
    displayOffTime = millis();

  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  switch (mode) {
    case 0:
      display.println("Mode: Off");
      break;
    case 1:
      display.println("Mode: 20%");
      break;
    case 2:
      display.println("Mode: 50%");
      break;
    case 3:
      display.println("Mode: 100%");
      break;
  }
  display.display();
  Serial.print("Display updated to: Mode ");
  Serial.println(mode);
}

void updatePWM() {
  switch (mode) {
    case 0:
      analogWrite(pwmPin, 0);
      break;
    case 1:
      analogWrite(pwmPin, 51); // 20% of 255
      break;
    case 2:
      analogWrite(pwmPin, 127); // 50% of 255
      break;
    case 3:
      analogWrite(pwmPin, 255); // 100% of 255
      break;
  }
  Serial.print("PWM signal set to: ");
  Serial.println(analogRead(pwmPin));
}
