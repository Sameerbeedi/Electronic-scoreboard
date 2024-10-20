# Badminton Scoreboard with Voice Control

## Description
This project is a Badminton scoreboard with support for push-button controls and voice recognition. It displays the scores and sets won by each player using an LCD display. The game ends when one player wins the required number of sets (default: best of 3). The project includes two modes:
- **Button-controlled mode:** Use physical push buttons to increase the scores of Player 1 and Player 2.
- **Voice-controlled mode:** Uses a voice recognition module to recognize specific voice commands for scoring and game management.

## Project Files
- **`miniproject.ino`**: This script handles the scoreboard logic using push buttons. It tracks points and sets won by each player and displays the scores on an LCD.
- **`vr_mod.ino`**: This script integrates voice recognition using the Elechouse Voice Recognition V3 module. It listens for voice commands like "Player 1", "Player 2", "Advantage", and "Deuce" to update the scores and game status on the LCD.

## Hardware Requirements
- Breadboard
- Wires
- 16x2 LCD display
- 2 Push buttons
- Arduino board (e.g., Arduino Uno)
- Elechouse Voice Recognition V3 module
- 10kΩ resistors (for pull-up configuration with buttons)

## Software Requirements
- Arduino IDE
- `LiquidCrystal` library for LCD control
- `SoftwareSerial` library for serial communication with the voice recognition module

## Getting Started

### Wiring Setup
1. **LCD Connection**:
   - RS pin to digital pin 12
   - EN pin to digital pin 11
   - D4 to digital pin 7
   - D5 to digital pin 6
   - D6 to digital pin 5
   - D7 to digital pin 4

2. **Push Buttons**:
   - Connect one button between A0 and GND.
   - Connect the other button between A2 and GND.
   - Use a 10kΩ resistor as a pull-up for each button.

3. **Voice Recognition Module**:
   - Connect the `TX` of the Voice Recognition module to Arduino digital pin 2.
   - Connect the `RX` of the Voice Recognition module to Arduino digital pin 3.

### Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Sameerbeedi/badminton-scoreboard.git
