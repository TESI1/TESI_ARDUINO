#include "DHT.h"
#include <LiquidCrystal.h>

#define NUMSENSORI 4

#define fotoresistenza A0
#define A_LINE 2
#define B_LINE 3
#define A_VAL 1
#define B_VAL 2
#define DHTPIN 7   
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

long numero_fin = 0x00;
long id_stanza = 0x01;
long id_sensore = 0x00;
long valore = 0x00;
long datiLetti[NUMSENSORI], tipoSensori[NUMSENSORI];


void setup() 
{
  pinMode(A_LINE, INPUT_PULLUP);
  pinMode(B_LINE, INPUT_PULLUP);
  
  tipoSensori[0] = 0x0B;
  tipoSensori[1] = 0x0A;
  tipoSensori[2] = 0x0C;
  tipoSensori[3] = 0x0D;
  lcd.begin(16, 2);
  lcd.print("ON: ");
  Serial.begin(9600);
  dht.begin();
}

void loop() 
{ 
  lcd.setCursor(4, 0);
  lcd.print(millis() / 1000);
  
  datiLetti[0] = (long)dht.readHumidity();
  datiLetti[1] = (long)dht.readTemperature();
  datiLetti[2] = (long)analogRead(fotoresistenza);
  datiLetti[3] = (long)((digitalRead(A_LINE) == HIGH) ? A_VAL : 0) + ((digitalRead(B_LINE) == HIGH) ? B_VAL : 0);
  
  for (int i = 0 ; i < NUMSENSORI ; i++) {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    numero_fin = 0;
    id_sensore = tipoSensori[i];
    
    numero_fin = (id_stanza<<24) + (id_sensore<<16) + datiLetti[i];
    Serial.println(numero_fin);
    lcd.print(numero_fin, HEX);
    delay(500);
  }
  
/*  float t = dht.readTemperature();
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Temp=");
    Serial.print(t);
    Serial.print(" *C");
    delay(2000);
    Serial.print("Humidity=");
    Serial.print(h);
    Serial.print("% ");
    delay(500);
   }*/
}
