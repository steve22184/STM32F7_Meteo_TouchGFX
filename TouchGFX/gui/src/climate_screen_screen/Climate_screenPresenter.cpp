#include <gui/climate_screen_screen/Climate_screenView.hpp>
#include <gui/climate_screen_screen/Climate_screenPresenter.hpp>

Climate_screenPresenter::Climate_screenPresenter(Climate_screenView& v)
    : view(v)
{

}

void Climate_screenPresenter::activate()
{
	// ensure the timeliness of the animations
	HAL::getInstance()->setFrameRateCompensation(true);

}

void Climate_screenPresenter::deactivate()
{
	HAL::getInstance()->setFrameRateCompensation(false);

}
