/*****************************************
This is a library for the BH1750FVI Lightsensor Module

You'll find an example which should enable you to use the library. 

You are free to use it, change it or build on it. In case you like it, it would be cool 
if you give it a star.

If you find bugs, please inform me!

Written by Wolfgang (Wolle) Ewald
https://wolles-elektronikkiste.de

*******************************************/


#ifndef BH1750_WE_H
#define BH1750_WE_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <Wire.h>

typedef enum BH1750Mode {
    CHM =     0b00010000,   //CHM: Continuously H-Resolution Mode
    CHM_2 =   0b00010001,   //CHM_2: Continuously H-Resolution Mode2
    CLM =     0b00010011,   //CLM: Continuously L-Resolution Mode
    OTH =     0b00100000,   //OTH: One Time H-Resolution Mode
    OTH_2 =   0b00100001,   //OTH_2: One Time H-Resolution Mode2
    OTL =     0b00100011    //OTL: One Time L-Resolution Mode
}bh1750_mode;


class BH1750_WE{
    public:
        static constexpr uint8_t DATA_REG_RESET{0b00000111};   
		static constexpr uint8_t POWER_DOWN    {0b00000000};  
		static constexpr uint8_t POWER_ON 	   {0b00000001};   
		
		BH1750_WE(const uint8_t addr = 0x23) : _wire{&Wire}, I2C_Address{addr} {}
        BH1750_WE(TwoWire *w, const uint8_t addr = 0x23) : _wire{w}, I2C_Address{addr} {}
        void init();
        void setMeasuringTimeFactor(float f);
        void setMode(bh1750_mode d_mode);
        float getLux();
        void resetDataReg();
        void powerOn();
        void powerDown();
                    
    protected:
        void setI2C_Address(uint8_t addr);
        void writeBH1750_WE(uint8_t);
        uint16_t readBH1750_WE();
        TwoWire *_wire;
        float lux;
        uint8_t I2C_Address;
        float mtf;      //measuring time factor
        bh1750_mode deviceMode;
};

#endif

