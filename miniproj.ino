#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int pushButton1 = A0;
const int pushButton2 = A2;

int count1 = 0;
int count2 = 0;
int setCount1 = 0;
int setCount2 = 0;
int gameWinner = 0; 
int setsToWin = 2; 
int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;


void setup() {
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  
  Serial.begin(9600); 
  lcd.begin(16, 2);
  updateLCD();
}

void loop() {
  addPoint();
  checkWinner(); 

  // Check if both players have won two sets or if three sets have been played
  if ((setCount1 == setsToWin && setCount2 < setsToWin) || (setCount1 < setsToWin && setCount2 == setsToWin) || (setCount1 == setsToWin && setCount2 == setsToWin)) {
    // End the program and declare the winner
    if (setCount1 > setCount2) {
      lcd.clear();
      lcd.print("Player 1 wins ");
    } else if (setCount2 > setCount1) {
      lcd.clear();
      lcd.print("Player 2 wins ");
    } 
    while (true) {} // End the game loop
  }
}

void addPoint() {
  int buttonState1 = digitalRead(pushButton1);
  int buttonState2 = digitalRead(pushButton2);

  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == LOW && (count1 <= 20 || (count1 - count2) < 2)) {
      count1++;
      updateLCD();
    }
  }

  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == LOW && (count2 <= 20 || (count2 - count1) < 2)) {
      count2++;
      updateLCD();
    }
  }

  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
}

void updateLCD() {
  lcd.clear(); // Clear the LCD before updating
  lcd.setCursor(0, 0);
  lcd.print("Player1: ");
  lcd.print(count1);
  lcd.print("  ");
  lcd.print(min(setCount1, 2)); // Limit set count to 2

  lcd.setCursor(0, 1);
  lcd.print("Player2: ");
  lcd.print(count2);
  lcd.print("  ");
  lcd.print(min(setCount2, 2)); // Limit set count to 2
}

void set(int player, int setCount) {
  lcd.print("Player ");
  lcd.print(player);
  lcd.print(" won set ");
  lcd.print(setCount);
  delay(2000); 
  count1 = 0;
  count2 = 0;
  lcd.clear(); 
}

void win(int player) {
  lcd.print("Player ");
  lcd.print(player);
  lcd.print(" won the game!");
}

void checkWinner() {
  if (count1 >= 21 && count1 - count2 >= 2) {
    setCount1++;
    if (setCount1 == setsToWin) {
      gameWinner = 1;
      win(1);
    } else {
      set(1, setCount1);
    }
    updateLCD(); 
  }
  
  if (count2 >= 21 && count2 - count1 >= 2) {
    setCount2++;
    if (setCount2 == setsToWin) {
      gameWinner = 2;
      win(2);
    } else {
      set(2, setCount2);
    }
    updateLCD(); 
  }
}