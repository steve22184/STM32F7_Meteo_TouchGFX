#ifndef CLIMATE_SCREENVIEW_HPP
#define CLIMATE_SCREENVIEW_HPP

#include <gui_generated/climate_screen_screen/Climate_screenViewBase.hpp>
#include <gui/climate_screen_screen/Climate_screenPresenter.hpp>

class Climate_screenView : public Climate_screenViewBase
{
public:
    Climate_screenView();
    virtual ~Climate_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:

private:
    float yAngleT;
    float yAngleH;
    float deltaYangleT;
    float deltaYangleH;

    uint16_t old_mantissa, old_fraction, old_hum;

};

#endif // CLIMATE_SCREENVIEW_HPP
