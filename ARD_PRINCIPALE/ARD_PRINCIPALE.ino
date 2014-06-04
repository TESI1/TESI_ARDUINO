#include <LiquidCrystal.h>
#include <ble_shield.h>
#include <services.h>
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <services.h>



long valoreInIngresso = 0;
String inString = "";    // string to hold input
int stanza = 0;
int sensore = 0;
int valore = 0;
LiquidCrystal lcd(20, 21, 7, 6, 5, 4);

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("ON: ");
  ble_begin();//init-start BLE
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print(millis() / 1000);
  
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
     
      
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      valoreInIngresso = inString.toInt();
     
      stanza  = (valoreInIngresso & 0xFF000000) >>24;
      sensore = (valoreInIngresso & 0x00FF0000) >>16;
      valore  = (valoreInIngresso & 0x0000FFFF);
      
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(valoreInIngresso, HEX);

      switch (sensore) {
        case 0x0A:
          break;
        case 0x0B:
          break;
        case 0x0C:
          break;
        default:
          stanza = -1;
          sensore = -1;
          valore = -1;
          break;
      }
          
      ble_write(stanza);
      ble_write(sensore);
      ble_write(valore);
     
      inString = "";
      
      ble_do_events();//permetto alla scheda di inviare e ricevere dati
    }     
  }     
}

