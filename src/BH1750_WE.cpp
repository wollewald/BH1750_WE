/*****************************************
This is a library for the BH1750FVI Lightsensor Module

You'll find an example which should enable you to use the library. 

You are free to use it, change it or build on it. In case you like it, it would be cool 
if you give it a star.

If you find bugs, please inform me!

Written by Wolfgang (Wolle) Ewald
https://wolles-elektronikkiste.de

*******************************************/

#include "BH1750_WE.h"

uint8_t BH1750_WE::init(){
    uint8_t success = setMode(CHM);
    setMeasuringTimeFactor(1.0);
    return success;
}

void BH1750_WE::setMeasuringTimeFactor(float f){
    mtf = f;
    writeBH1750_WE(deviceMode);
    byte mt = round(mtf*69);
    byte highByteMT = ((mt>>5) | 0b01000000);
    byte lowByteMT = (mt & 0b01111111);
    lowByteMT |= 0b01100000;
    writeBH1750_WE(highByteMT);
    writeBH1750_WE(lowByteMT);
    delay(200);
}

uint8_t BH1750_WE::setMode(BH1750Mode d_mode){
    deviceMode = d_mode;
    return !writeBH1750_WE(deviceMode);
}

float BH1750_WE::getLux(){
    uint16_t rawLux;
    rawLux = readBH1750_WE();
    if((deviceMode==CHM_2)||(deviceMode==OTH_2)){
    lux = (rawLux/2.4)/mtf;     
  }
  else{
    lux = (rawLux/1.2)/mtf;
  }
  return lux;
    
}

void BH1750_WE::resetDataReg(){
    writeBH1750_WE(DATA_REG_RESET);
}

void BH1750_WE::powerOn(){
    writeBH1750_WE(POWER_ON);
}

void BH1750_WE::powerDown(){
    writeBH1750_WE(POWER_DOWN);
}

/************************************************ 
    private functions
*************************************************/


void BH1750_WE::setI2C_Address(uint8_t addr){
    I2C_Address = addr;
}

uint8_t BH1750_WE::writeBH1750_WE(uint8_t val){
    _wire->beginTransmission(I2C_Address);
    _wire->write(val);
    return _wire->endTransmission();
}

uint16_t BH1750_WE::readBH1750_WE(){
    uint8_t MSbyte = 0, LSbyte = 0;
    _wire->requestFrom(I2C_Address, static_cast<uint8_t>(2));
    if(_wire->available()){
        MSbyte=_wire->read();
        LSbyte=_wire->read(); 
    }
    return ((MSbyte<<8) + LSbyte);
}   
    


