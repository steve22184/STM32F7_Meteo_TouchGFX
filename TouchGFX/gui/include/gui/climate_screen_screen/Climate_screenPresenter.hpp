#ifndef CLIMATE_SCREENPRESENTER_HPP
#define CLIMATE_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Climate_screenView;

class Climate_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Climate_screenPresenter(Climate_screenView& v);

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

    virtual ~Climate_screenPresenter() {};

    uint16_t getTempMantissa (void){
    	return model->getTempMantissa();
    }

    uint16_t getTempFraction (void){
    	return model->getTempFraction();
    }

    uint8_t getHumidity()
    {
    	return model->getHumidity();
    }

private:
    Climate_screenPresenter();

    Climate_screenView& view;
};

#endif // CLIMATE_SCREENPRESENTER_HPP
