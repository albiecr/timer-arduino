#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins
const int buttonSetTime = 2;    // Button D2 - start
const int buttonAdd30s = 3;     // Button D3 - add 30s
const int buttonStop = 4;       // Button D4 - stop
const int ledGreen = 5;
const int ledRed = 6;
const int buzzer = 7;

// Time
int minutes = 0;
int extraSeconds = 0;
int totalSeconds;
bool timerRunning = false;
unsigned long startTime;
int remainingSecondsAtStop = 0; // Stores remaining time when stopped
bool timerPaused = false;       // Indicates if the timer is paused

// Button states
bool lastStartButtonState = HIGH;
bool lastAddButtonState = HIGH;
bool lastStopButtonState = HIGH;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(buttonSetTime, INPUT_PULLUP);
  pinMode(buttonAdd30s, INPUT_PULLUP);
  pinMode(buttonStop, INPUT_PULLUP);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  updateDisplay();
}

void loop() {
  unsigned long now = millis();

  // Read current button states
  bool currentStartButtonState = digitalRead(buttonSetTime);
  bool currentAddButtonState = digitalRead(buttonAdd30s);
  bool currentStopButtonState = digitalRead(buttonStop);

  // Button D3 pressed (edge HIGH to LOW)
  if (!timerRunning && lastAddButtonState == HIGH && currentAddButtonState == LOW) {
    // Only allow adjustment if timer is not running and not paused
    if (!timerPaused) {
      extraSeconds += 30;
      if (extraSeconds >= 60) {
        extraSeconds -= 60;
        minutes++;
      }
      updateDisplay();
      feedbackAjuste();
      delay(200);  // debounce
    }
  }

  // Button D2 pressed (edge HIGH to LOW)
  if (lastStartButtonState == HIGH && currentStartButtonState == LOW) {
    if (!timerRunning && !timerPaused) {
      // Timer stopped and not paused = start from configured time
      startTimer();
    } else if (!timerRunning && timerPaused) {
      // Timer paused, resume from where it stopped
      resumeTimer();
    }
    delay(200);  // debounce
  }

  // Button D4 pressed to stop the countdown (edge HIGH to LOW)
  if (timerRunning && lastStopButtonState == HIGH && currentStopButtonState == LOW) {
    stopTimer();
    delay(200);  // debounce
  }

  // Update previous button states
  lastAddButtonState = currentAddButtonState;
  lastStartButtonState = currentStartButtonState;
  lastStopButtonState = currentStopButtonState;

  // Countdown logic
  if (timerRunning) {
    unsigned long elapsedSeconds = (millis() - startTime) / 1000;
    int remainingSeconds = totalSeconds - elapsedSeconds;

    if (remainingSeconds >= 0) {
      remainingSecondsAtStop = remainingSeconds; // update remaining time every second
      static unsigned long lastUpdate = 0;
      if (millis() - lastUpdate >= 1000) {
        lastUpdate = millis();
        updateCountdownDisplay(remainingSeconds);
      }
    } else {
      endTimer();
    }
  }
}

void startTimer() {
  timerRunning = true;
  timerPaused = false;
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  startTime = millis();
  totalSeconds = (minutes * 60) + extraSeconds;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown");
  lcd.setCursor(0, 1);
  lcd.print("Started!");
  delay(1000);
}

void resumeTimer() {
  timerRunning = true;
  timerPaused = false;
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);

  totalSeconds = remainingSecondsAtStop;
  startTime = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown");
  lcd.setCursor(0, 1);
  lcd.print("Resumed!");
  delay(1000);
}

void stopTimer() {
  timerRunning = false;
  timerPaused = true;
  digitalWrite(ledGreen, LOW);

  // Show message with remaining time on stop
  int displayMinutes = remainingSecondsAtStop / 60;
  int displaySeconds = remainingSecondsAtStop % 60;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown stopped");
  lcd.setCursor(0, 1);
  if (displayMinutes < 10) lcd.print("0");
  lcd.print(displayMinutes);
  lcd.print(":");
  if (displaySeconds < 10) lcd.print("0");
  lcd.print(displaySeconds);

  Serial.print("Countdown stopped at ");
  if (displayMinutes < 10) Serial.print("0");
  Serial.print(displayMinutes);
  Serial.print(":");
  if (displaySeconds < 10) Serial.print("0");
  Serial.println(displaySeconds);
}

void endTimer() {
  timerRunning = false;
  timerPaused = false;
  digitalWrite(ledGreen, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TIME'S UP!");
  lcd.setCursor(0, 1);
  lcd.print("00:00");

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledRed, HIGH);
    tone(buzzer, 1000, 500);
    delay(500);
    digitalWrite(ledRed, LOW);
    delay(500);
  }

  noTone(buzzer);
  digitalWrite(ledRed, LOW);

  // Reset values
  minutes = 1;
  extraSeconds = 0;
  remainingSecondsAtStop = 0;
  updateDisplay();
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set the time:");
  lcd.setCursor(0, 1);
  lcd.print(minutes);
  lcd.print(" min ");
  lcd.print(extraSeconds);
  lcd.print(" sec");

  Serial.print("Time: ");
  Serial.print(minutes);
  Serial.print(" min ");
  Serial.print(extraSeconds);
  Serial.println(" sec");
}

void updateCountdownDisplay(int remainingSeconds) {
  int displayMinutes = remainingSeconds / 60;
  int displaySeconds = remainingSeconds % 60;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time remaining:");
  lcd.setCursor(0, 1);
  if (displayMinutes < 10) lcd.print("0");
  lcd.print(displayMinutes);
  lcd.print(":");
  if (displaySeconds < 10) lcd.print("0");
  lcd.print(displaySeconds);

  Serial.print("Countdown: ");
  if (displayMinutes < 10) Serial.print("0");
  Serial.print(displayMinutes);
  Serial.print(":");
  if (displaySeconds < 10) Serial.print("0");
  Serial.println(displaySeconds);
}

void feedbackAjuste() {
  digitalWrite(ledGreen, HIGH);
  delay(100);
  digitalWrite(ledGreen, LOW);
}

