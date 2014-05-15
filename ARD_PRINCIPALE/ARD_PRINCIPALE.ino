/*
  String to Integer conversion

 Reads a serial input string until it sees a newline, then converts
 the string to a number if the characters are digits.

 The circuit:
 No external components needed.

 created 29 Nov 2010
 by Tom Igoe

 This example code is in the public domain.
 */
long valoreInIngresso = 0;
String inString = "";    // string to hold input
byte stanza = 0;
byte sensore = 0;
byte valore = 0;


void setup() {
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
     
      stanza = (valoreInIngresso & 0xFF0000) >>16;
      sensore = (valoreInIngresso & 0x00FF00) >>8;
      valore = (valoreInIngresso & 0x0000FF);
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
}

