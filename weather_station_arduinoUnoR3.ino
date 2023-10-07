#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "CRC8.h"
//#include "CRC.h"
 


Adafruit_BMP085 bmp;
int sensor_A3=A3;
int wartosc_A3;
int sensor_A0 = A0;    // podłączenie od A0 na czujniku do A0 na Arduino
int sensor_D0 = 2;     // podłączenie od D0 na czujniku do pinu 2 na Arduino
int rain;        // zmienna dla wartości A0
int wartosc_D0;        // zmienna dla wartości A0
float temp;
int pressure;
int Light;
//String Str;

//char * msg;
CRC8 crc;

void GetData(/*int &Rain, int &Press, double &Tmp, int Light*/)
{
  temp=bmp.readTemperature();
  pressure=bmp.readPressure() / 100;
  rain = analogRead(sensor_A0);      // pobranie wartości z A0
  Light=analogRead(sensor_A3);
}

int CalculateCRC8()
{  
  GetData();
  String  Str="A "+ String((int)(temp*10))+ " " +String(pressure)+
    " " +String(rain)+ " " + String(Light);
  char * msg=Str.c_str();
  CRC8 crc;

  Serial.println();
  Serial.println();
  Serial.println(Str);
  Serial.println(Str.length());
  crc.setPolynome(0x07);
  crc.add((uint8_t*)msg,Str.length());
  Serial.println(crc.getCRC(), HEX);
  Serial.println(msg);

}



void DisplayMess()
{
  Serial.print("A ");
  Serial.print(temp,1);
  Serial.print(" ");
  Serial.print(pressure);
  Serial.print(" ");
  Serial.print(rain);
  Serial.print(" ");
  Serial.print(Light);


  Serial.println();
}
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);    // ustawienie pinu 2 jako wejście

  crc.setPolynome(0x07);
  if (!bmp.begin())
  {
    Serial.println("Nie odnaleziono czujnika BMP085 / BMP180");
    while (1) {}
  }
}

void loop()
{
 
  CalculateCRC8();

  delay(3000);
}

 
