#ifndef LIQUIDCRYSTAL_INCLUDED
#define LIQUIDCRYSTAL_INCLUDED

#include "gmock/gmock.h"

class LiquidCrystal
{
    public: 
        virtual ~LiquidCrystal(){}

        MOCK_METHOD2( begin, void (uint8_t, uint8_t));
        MOCK_METHOD1( print, void (string));
        MOCK_METHOD2( setCursor, void (uint8_t , uint8_t ));
        MOCK_METHOD0( clear, void() );

        LiquidCrystal(uint8_t rs,  uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
        {
        }
};

#endif 
