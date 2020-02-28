#ifndef MODEL_HPP
#define MODEL_HPP

#include "stdint.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();


    void saveHour(uint8_t saveHour)
    {
    	hour = saveHour;
    }

    void saveMinute(uint8_t saveMinute)
    {
    	minute = saveMinute;
    }

    void saveSecond(uint8_t saveSecond)
    {
    	second = saveSecond;
    }

    uint8_t getHour()
    {
    	return hour;
    }

    uint8_t getMinute()
    {
    	return minute;
    }

    uint8_t getSecond()
    {
    	return second;
    }

    uint8_t getSetupFlag()
    {
    	return setup_flag;
    }
    void setSetupFlag()
    {
    	setup_flag = 1;
    }

protected:
    ModelListener* modelListener;
    uint8_t hour, minute, second, setup_flag;
};

#endif // MODEL_HPP
