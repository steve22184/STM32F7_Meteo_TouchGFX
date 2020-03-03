#ifndef CLOCK_SCREENVIEW_HPP
#define CLOCK_SCREENVIEW_HPP

#include <gui_generated/clock_screen_screen/Clock_screenViewBase.hpp>
#include <gui/clock_screen_screen/Clock_screenPresenter.hpp>

class Clock_screenView : public Clock_screenViewBase
{
public:
    Clock_screenView();
    virtual ~Clock_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void hplusClicked();
    virtual void hminusClicked();
    virtual void mplusClicked();
    virtual void mminusClicked();
    virtual void setupClicked();
protected:

private:
    uint8_t hour, minute, second;
};

#endif // CLOCK_SCREENVIEW_HPP
