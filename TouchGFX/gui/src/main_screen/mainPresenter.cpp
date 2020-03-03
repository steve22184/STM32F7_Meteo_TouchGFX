#include <gui/main_screen/mainView.hpp>
#include <gui/main_screen/mainPresenter.hpp>

mainPresenter::mainPresenter(mainView& v)
    : view(v)
{

}

void mainPresenter::activate()
{
	// ensure the timeliness of the animations
	HAL::getInstance()->setFrameRateCompensation(true);
}

void mainPresenter::deactivate()
{
	HAL::getInstance()->setFrameRateCompensation(false);
}
