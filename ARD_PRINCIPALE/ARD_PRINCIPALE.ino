#include <ble_shield.h>
#include <services.h>
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <services.h>

long valoreInIngresso = 0;
String inString = "";    // string to hold input
byte stanza = 0;
byte sensore = 0;
byte valore = 0;
//byte checksum = 0;
//byte checksumTrasm = 0;


void setup() 
{
  ble_begin();//init-start BLE
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
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
     
      //checksumTrasm = (valoreInIngresso & 0xFF000000) >>24;
      stanza = (valoreInIngresso & 0x00FF0000) >>16;
      sensore = (valoreInIngresso & 0x0000FF00) >>8;
      valore = (valoreInIngresso & 0x000000FF);
      
      //checksum = (~ (stanza + sensore + valore)) & 0xff; 
      
      //if (checksumTrasm == checksum)
      //if (true)
      
        ble_write(stanza);
        ble_write(sensore);
        ble_write(valore);
     
      //}
     
      /*
       Serial.print("stanza:");
      Serial.println(stanza, HEX);

      Serial.print("SEnsore:");
      Serial.println(sensore,HEX);

      Serial.print("valore:");
      Serial.println(valore);
      */
      // clear the string for new input:
      inString = "";   
    }
     
  }
  ble_do_events();//permetto alla scheda di inviare e ricevere dati     
}

