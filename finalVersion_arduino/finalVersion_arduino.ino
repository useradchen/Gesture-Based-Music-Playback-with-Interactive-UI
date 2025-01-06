#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD initialization, note that the I2C address may need to be changed to 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pin definitions
const int playLed = 2;  // green
const int pauseLed = 3; // red
const int nextLed = 4;  // yellow
const int prevLed = 5;  // white

// Potentiometer pin definition
const int potPin = A0;  // Analog pin connected to the potentiometer

// Volume state
int volume = 0;
int receivedVolume = -1;  // Used to store volume received from Python

// Currently playing song name
String currentSong = "No Song";

// Scroll display settings
unsigned long previousMillis = 0;  // Store the last update time
const long interval = 300;         // Scroll update interval (300 milliseconds)
int songStartPos = 0;  // Starting position for scrolling song name

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Ensure I2C initialization

  // Initialize the LCD and turn on the backlight
  lcd.begin(16, 2);  // Initialize the LCD display
  lcd.backlight();   // Turn on the backlight

  // Set LED pins as output
  pinMode(playLed, OUTPUT);
  pinMode(pauseLed, OUTPUT);
  pinMode(nextLed, OUTPUT);
  pinMode(prevLed, OUTPUT);

  // Set potentiometer pin as input
  pinMode(potPin, INPUT);

  resetLeds();

  // Clear the screen and display initial message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000); // Delay to display the message
  lcd.clear(); // Clear the screen
}

void loop() {
  // Receive volume value from Python
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove extra spaces or newlines
    if (input.startsWith("Volume:")) {
      // If the received data is volume, update volume
      receivedVolume = input.substring(7).toInt(); // Extract and convert volume value to integer
    } else {
      // Handle other commands or song names
      processInput(input);
    }
  }

  // Read potentiometer value to adjust volume (if volume not set via potentiometer)
  if (receivedVolume == -1) {
    int potValue = analogRead(potPin);  // Read potentiometer value (0 to 1023)
    adjustVolume(potValue);
  } else {
    // If volume value is received, use it directly
    volume = receivedVolume;
    receivedVolume = -1;  // Reset received volume marker
  }

  // Send volume to Python
  sendVolumeToPython(volume);

  // Update volume display
  lcd.setCursor(0, 1);
  lcd.print("Volume: ");
  lcd.print(volume);
  lcd.print("   ");  // Clear previous digits on the display

  // Scroll song name
  scrollSongName();
}

// Handle input (commands or song names)
void processInput(String input) {
  // Turn on the corresponding LED based on the command
  if (input == "Play") {
    if (digitalRead(playLed) == LOW) { // If Play LED is off, turn it on
      resetLeds(); // Reset all LEDs
      digitalWrite(playLed, HIGH); // Turn on Play LED
    }
  } else if (input == "Pause") {
    if (digitalRead(pauseLed) == LOW) { // If Pause LED is off, turn it on
      resetLeds(); // Reset all LEDs
      digitalWrite(pauseLed, HIGH); // Turn on Pause LED
    }
  } else if (input == "Next") {
    resetLeds(); // Reset all LEDs
    digitalWrite(nextLed, HIGH); // Turn on Next LED
    delay(500);  // Keep Next LED on for 500 milliseconds
    digitalWrite(nextLed, LOW); // Turn off after 500 milliseconds
  } else if (input == "Previous") {
    resetLeds(); // Reset all LEDs
    digitalWrite(prevLed, HIGH); // Turn on Previous LED
    delay(500);  // Keep Previous LED on for 500 milliseconds
    digitalWrite(prevLed, LOW); // Turn off after 500 milliseconds
  } else {
    // Handle other input (song name)
    currentSong = input;
    songStartPos = 0;  // Reset scrolling start position
  }
}

// Volume adjustment logic
void adjustVolume(int potValue) {
  // Map potentiometer value from 0~1023 to volume range of 0~100
  volume = map(potValue, 0, 1023, 0, 100);
}

// Scroll song name
void scrollSongName() {
  unsigned long currentMillis = millis();
  
  // Scroll every 300 milliseconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // If song name length exceeds 16 characters, start scrolling
    if (currentSong.length() > 16) {
      // Display 16 characters from the current start position
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(currentSong.substring(songStartPos, songStartPos + 16));

      // Update start position for cyclic scrolling
      songStartPos++;
      if (songStartPos + 16 > currentSong.length()) {
        songStartPos = 0; // Restart scrolling from the beginning
      }
    } else {
      // If song name is short, display it directly
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(currentSong);
    }
  }
}

// Reset all LED states
void resetLeds() {
  digitalWrite(playLed, LOW);
  digitalWrite(pauseLed, LOW);
  digitalWrite(nextLed, LOW);
  digitalWrite(prevLed, LOW);
}

// Send volume to Python
void sendVolumeToPython(int volume) {
  Serial.print("Volume: ");
  Serial.println(volume);  // Send volume value to Python
}
