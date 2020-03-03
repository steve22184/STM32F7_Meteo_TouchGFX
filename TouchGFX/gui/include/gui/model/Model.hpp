#ifndef MODEL_HPP
#define MODEL_HPP

#include "stdint.h"

#ifndef SIMULATOR
#include "at24c256.hpp"
#endif

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

    uint16_t getTempMantissa (void){
    	return temp_mantissa;
    }

    uint16_t getTempFraction (void){
    	return temp_fraction;
    }

    uint8_t getHumidity (void){
    	return humidity;
    }

    void readNewQuote(){
#ifndef SIMULATOR
    	app::eeprom().read_cluster();
#endif
    }

    uint8_t getQuotesFlag(){
    	return eeprom_flag;
    }

    uint8_t* getQuotes(){
    	uint8_t *temp = 0;
#ifndef SIMULATOR
    	temp =  app::eeprom().get_data();
#endif
    	return temp;
    }

    void setSliderValue (int val){
    	slider_val = val;
    }

    int getSliderValue(void){
    	return slider_val;
    }

    void setQuoteX(int16_t qx_){
    	qx = qx_;
    }
    void setQuoteY(int16_t qy_){
    	qy = qy_;
    }
    void setClockSetX(int16_t csx_){
    	csx = csx_;
    }
    void setClockSetY(int16_t csy_){
    	csy = csy_;
    }
    int16_t getQuoteX(void){
    	return qx;
    }
    int16_t getQuoteY(void){
    	return qy;
    }
    int16_t getClockSetX(void){
    	return csx;
    }
    int16_t getClockSetY(void){
    	return csy;
    }

protected:
    ModelListener* modelListener;
    uint8_t hour, minute, second, setup_flag, humidity, eeprom_flag;
    uint16_t temp_mantissa, temp_fraction;
    int16_t qx, qy, csx, csy;
    int slider_val;
};

#endif // MODEL_HPP
