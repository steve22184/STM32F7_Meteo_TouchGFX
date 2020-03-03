#include <gui/clock_screen_screen/Clock_screenView.hpp>
#include <gui/clock_screen_screen/Clock_screenPresenter.hpp>

Clock_screenPresenter::Clock_screenPresenter(Clock_screenView& v)
    : view(v)
{

}

void Clock_screenPresenter::activate()
{
	// ensure the timeliness of the animations
		    HAL::getInstance()->setFrameRateCompensation(true);
}

void Clock_screenPresenter::deactivate()
{
	HAL::getInstance()->setFrameRateCompensation(false);
}
