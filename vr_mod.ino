#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//int x=8; //button is connected to digital pin 8
//int val=0


VR myVR(2,3);


uint8_t records[7]; // save record
uint8_t buf[64];


#define player1 (0)
#define player2 (1)
#define adv (2)
#define deuce (3)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  lcd.begin(16,2);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");

  uint8_t records[] = {player1,player2,adv,deuce};
  myVR.load(records, sizeof(records)); // Load multiple records


  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);             
  }
  
  if(myVR.load((uint8_t)player1) >= 0){
    Serial.println("player1 loaded");
  }

  if(myVR.load((uint8_t)player2) >= 0){
    Serial.println("player2 loaded");
  }
  
  if(myVR.load((uint8_t)adv) >= 0){
    Serial.println("advantage loaded");
  }

  if(myVR.load((uint8_t)deuce) >= 0){
    Serial.println("deuce loaded");
  }
  // Load more commands as needed

  
} 

void loop() {
    int ret = myVR.recognize(buf, 50); // Recognize voice commands
    if (ret > 0) {
        switch(buf[1]) {
            case player1:
                lcd.clear();
                lcd.print("Player 1: 1");
                break;
            
            case player2:
                lcd.clear();
                lcd.print("Player 2: 1");
                break;

            case adv:
                lcd.clear();
                lcd.print("Advantage!");
                break;

            case deuce:
                lcd.clear();
                lcd.print("Its a deuce!");
                break;
            // Add cases for more commands
            default:
                lcd.clear();
                lcd.print("Unknown Command");
                break;
        }
        printVR(buf);
    }
}

