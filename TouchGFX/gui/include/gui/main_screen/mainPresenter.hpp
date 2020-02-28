#ifndef MAINPRESENTER_HPP
#define MAINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class mainView;

class mainPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    mainPresenter(mainView& v);

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

    virtual ~mainPresenter() {};

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

private:
    mainPresenter();

    mainView& view;
};

#endif // MAINPRESENTER_HPP
