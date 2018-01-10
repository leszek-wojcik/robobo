#ifndef ROBOBO_MOTORI_INCLUDED
#define ROBOBO_MOTORI_INCLUDED

class MotorI
{
    public:
        virtual void setPosition(int32_t) = 0;
        virtual int32_t getPosition() = 0;
        virtual void stop(void) = 0;

};
#endif 
