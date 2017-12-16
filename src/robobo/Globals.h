#ifndef ROBOBO_GLOBALS_INCLUDED
#define ROBOBO_GLOBALS_INCLUDED
class Globals
{
    private:
        Globals();
    public:
        static Globals* instance; 
        static Globals* getInstance();
        static Globals* createInstance();

        // Encoders
        int encoder1aPin;
        bool encoder1aVal;

        int encoder1bPin;
        bool encoder1bVal;

        int encoder2aPin;
        bool encoder2aVal;

        int encoder2bPin;
        bool encoder2bVal;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
