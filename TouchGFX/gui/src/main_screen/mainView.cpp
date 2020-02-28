#include <gui/main_screen/mainView.hpp>

mainView::mainView() :

	xAngleTGFX(0.0f),
	yAngleTGFX(0.0f),
	zAngleTGFX(0.0f),
	yAngleT(0.0f),
	yAngleH(0.0f),
	deltaXangleTGFX(0.032f),
	deltaYangleTGFX(0.029f),
	deltaZangleTGFX(0.027f),
	deltaYangleT(0.029f),
	deltaYangleH(0.029f),

	hour(0),
	minute(0),
	second(0)
	{

	}

void mainView::setupScreen()
{
    mainViewBase::setupScreen();

    hour = presenter->getHour();
    minute = presenter->getMinute();
    second = presenter->getSecond();

    Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%d", hour);
    Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%d", minute);
}

void mainView::tearDownScreen()
{
    mainViewBase::tearDownScreen();
}

void mainView::handleTickEvent()
{
    // Update angle values

    xAngleTGFX += deltaXangleTGFX;
    yAngleTGFX += deltaYangleTGFX;
    zAngleTGFX += deltaZangleTGFX;

    yAngleT += deltaYangleT;
    yAngleH += deltaYangleH;

    // Update the images with the new angles
    // The image is automatically invalidated (the optimal minimal area).
    // If any of the set..() methods (e.g. setOrigo, setCamera, setRenderingAlgorithm...) are used
    // remember to manually invalidate the image afterwards (textureMapperImage2D.invalidate()).

    tgfx.updateAngles(xAngleTGFX, yAngleTGFX, zAngleTGFX);
    temp.updateAngles(0, yAngleT, 0);
    hum.updateAngles(0, yAngleH, 0);

    watch.setTime24Hour(presenter->getHour(), presenter->getMinute(), presenter->getSecond());
}

void mainView::hplusClicked(){
	hour == 23 ? hour = 0 : ++hour;
	Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%d", hour);
	hour_n.invalidate();
}
void mainView::hminusClicked(){
	hour == 0 ? hour = 23 : --hour;
	Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%d", hour);
	hour_n.invalidate();
}
void mainView::mplusClicked(){
	minute == 59 ? minute = 0 : ++minute;
	Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%d", minute);
	minute_n.invalidate();
}
void mainView::mminusClicked(){
	minute == 0 ? minute = 59 : --minute;
	Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%d", minute);
	minute_n.invalidate();
}
void mainView::setupClicked(){
	presenter->saveHour(hour);
	presenter->saveMinute(minute);

	presenter->setSetupFlag();
}
