# Gesture-Based-Music-Playback-with-Interactive-UI
Goal:Using Mediapipe Gestures to Play Music and Display Results in the UI
# Using Mediapipe Gestures to Play Music and Display Results in the UI

## 📖 Introduction
This project combines gesture recognition using MediaPipe and OpenCV with Arduino hardware to create a music control system. Hand gestures control music playback, track switching, and volume, with real-time feedback on an LED indicator, UI, and 1602 LCD.

## 🛠 Equipment
| Component               | Purpose                                    |
|-------------------------|--------------------------------------------|
| Arduino Uno             | Microcontroller for hardware integration  |
| LED                     | Indicator for gesture-based actions       |
| 1602 LCD                | Displays the current song name            |
| Variable Resistor (10K) | Adjusts the music volume                  |
| Breadboard & Dupont Line| Prototyping connections                   |

## 🖥 Features
1. **Gesture Recognition**  
   - Utilizes **MediaPipe** and **OpenCV** for recognizing specific hand gestures.

2. **Music Control, LED Indicator, and UI Feedback**  
   - Gestures control music playback and track switching.
   - LED colors indicate the current action.
   - A user interface displays playback status and song information.

3. **Current Song Display**  
   - The 1602 LCD shows the current song name in real time.

4. **Volume Control**  
   - A potentiometer adjusts the volume by sending resistance data to Python, which updates the system's volume.

---

## 🚀 System Workflow

### Gesture Recognition Process
1. OpenCV and MediaPipe detect gestures.
2. The gesture results and song name are returned to the Arduino via I2C.
3. LEDs and the UI reflect the current playback status.

![Gesture Recognition Workflow](link-to-image)

### Volume Adjustment Process
1. The potentiometer adjusts resistance.
2. The resistance value is sent back to Python via Arduino.
3. Python updates the volume accordingly.

![Volume Adjustment Workflow](link-to-image)

---

## ✋ Gesture Controls
| Gesture      | Action         | LED Color  |
|--------------|----------------|------------|
| Hand Open    | Play           | Green      |
| OK           | Pause          | Red        |
| One Finger   | Previous Track | White      |
| Two Fingers  | Next Track     | Yellow     |

---

## 🔌 Arduino UNO Pin Mapping

### I2C Connections
| Pin   | Arduino Uno Pin |
|-------|-----------------|
| VCC   | 5V             |
| GND   | GND            |
| SDA   | A4             |
| SCL   | A5             |

### Variable Resistor Connections
| Pin   | Arduino Uno Pin |
|-------|-----------------|
| A     | VCC            |
| B     | A0             |
| C     | GND            |

---

## 📋 Requirements
- Python 3.x
- MediaPipe
- OpenCV
- Arduino IDE
- Necessary libraries for the 1602 LCD and I2C communication.

---

## 🛠 Setup Instructions
1. **Hardware Assembly**  
   - Connect the Arduino to the LED, 1602 LCD, and variable resistor as per the pin mapping table.

2. **Install Dependencies**  
   ```bash
   pip install opencv-python mediapipe
