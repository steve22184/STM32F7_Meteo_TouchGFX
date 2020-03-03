#ifndef CLOCK_SCREENPRESENTER_HPP
#define CLOCK_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Clock_screenView;

class Clock_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Clock_screenPresenter(Clock_screenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Clock_screenPresenter() {};

    void saveHour(uint8_t hour)
        {
        	model->saveHour(hour);
        }

        void saveMinute(uint8_t minute)
        {
        	model->saveMinute(minute);
        }

        void saveSecond(uint8_t second)
        {
        	model->saveSecond(second);
        }

        uint8_t getHour()
        {
        	return model->getHour();
        }

        uint8_t getMinute()
        {
        	return model->getMinute();
        }

        uint8_t getSecond()
        {
        	return model->getSecond();
        }

        uint8_t getSetupFlag()
        {
        	return model->getSetupFlag();
        }
        void setSetupFlag()
        {
        	model->setSetupFlag();
        }

        void readNewQuote(){
        	model->readNewQuote();
        }

        uint8_t getQuotesFlag(){
        	return model->getQuotesFlag();
        }

        uint8_t* getQuotes(){
        	return model->getQuotes();
        }

        void setQuoteX(int16_t qx_){
        	model->setQuoteX(qx_);
        }
        void setQuoteY(int16_t qy_){
        	model->setQuoteY(qy_);
        }
        void setClockSetX(int16_t csx_){
        	model->setClockSetX(csx_);
        }
        void setClockSetY(int16_t csy_){
        	model->setClockSetY(csy_);
        }
        int16_t getQuoteX(void){
        	return model->getQuoteX();
        }
        int16_t getQuoteY(void){
        	return model->getQuoteY();
        }
        int16_t getClockSetX(void){
        	return model->getClockSetX();
        }
        int16_t getClockSetY(void){
        	return model->getClockSetY();
        }

private:
    Clock_screenPresenter();

    Clock_screenView& view;
};

#endif // CLOCK_SCREENPRESENTER_HPP
