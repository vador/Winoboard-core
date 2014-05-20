#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt=0 ;

byte accx,accy,zbut,cbut ;
int ledPin = 13 ;

void setup()
{
  Serial5.begin( 115200 ) ;
  Serial5.println("nunchuck_init");
  
  Wire.begin(); // join i2c bus as master
  Wire.beginTransmission(0x52);// transmit to device 0x52
    Wire.write((uint8_t)0x40);// sends memory address
    Wire.write((uint8_t)0x00);// sends sent a zero.
  Wire.endTransmission();// stop transmitting

  Serial5.println( "WiiChuckDemo ready" ) ;
  delay(3000);
}

void loop()
{
  Wire.requestFrom(0x52, 6);

  
  uint8_t jX = Wire.read();
  uint8_t jY = Wire.read();
  uint8_t accX = Wire.read();
  uint8_t accY = Wire.read();
  uint8_t accZ = Wire.read();
  uint8_t misc = Wire.read();
  
  Serial5.print("Joy : ");
  Serial5.print(jX);
  Serial5.print(", ");
  Serial5.print(jY);
  
  Serial5.print("\tAcc : ");
  Serial5.print(accX);
  Serial5.print(", ");
  Serial5.print(accY);
  Serial5.print(", ");
  Serial5.print(accZ);
  
  Serial5.print("\tBtn : ");
  switch(misc & 0x3ul)
  {
    case 0x0ul:
      Serial5.println("Z");
      break;

    case 0x1ul:
      Serial5.println("C");
      break;

    case 0x2ul:
      Serial5.println("C + Z");
      break;

    case 0x3ul:
      Serial5.println("No key");
      break;
    
    default:
      break;
  }

  
  Wire.beginTransmission(0x52);// transmit to device 0x52
    Wire.write((uint8_t)0x00);// sends sent a zero.
  Wire.endTransmission();// stop transmitting

  delay(100);
}