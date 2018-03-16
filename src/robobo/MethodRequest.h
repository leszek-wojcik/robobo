#ifndef METHOD_REQUEST_INCLUDED
#define METHOD_REQUEST_INCLUDED

#include <tuple>
#include "Arduino.h"
#include <functional>

class ActiveObject;

class MRequest
{
    public:
        MRequest(ActiveObject *a, std::function<void()> f,bool persistent=false):
            ao(a),
            persistent(persistent)
        {
            func = new std::function<void()>(f);
        }

        ActiveObject *ao;
        std::function<void()> *func;
        bool persistent;

        void setPersistent(bool p)
        {
            persistent = p;
        }
    
        bool isPersistent()
        {
            if (persistent)
                return true;
            else
                return false;
        }

        ActiveObject *getActiveObject()
        {
            return ao;
        }

        ~MRequest()
        {
            delete func;
        }
        
};




#endif
