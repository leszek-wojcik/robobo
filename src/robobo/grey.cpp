#include "grey.h"


uint8_t greyLookup[2][2] = {{2,1},{3,0}};

uint8_t greyValue(uint8_t a, uint8_t b)
{
    return greyLookup[a][b];
}
