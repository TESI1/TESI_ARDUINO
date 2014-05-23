#include "DHT.h"

#define NUMSENSORI 2

#define DHTPIN 7   
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

long numero_fin = 0x00;
long id_stanza = 0x01;
long id_sensore = 0x00;
long valore = 0x00;
long datiLetti[NUMSENSORI], tipoSensori[NUMSENSORI];

void setup() 
{
  tipoSensori[0] = 0x0B;
  tipoSensori[1] = 0x0A;
  Serial.begin(9600);
  dht.begin();
}

void loop() 
{
  datiLetti[0] = (long)dht.readHumidity();
  datiLetti[1] = (long)dht.readTemperature();
  
  for (int i = 0 ; i < NUMSENSORI ; i++) {
    numero_fin = 0;
    id_sensore = tipoSensori[i];
    numero_fin = (id_stanza<<16) + (id_sensore<<8) + datiLetti[i];
    Serial.println(numero_fin);
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
