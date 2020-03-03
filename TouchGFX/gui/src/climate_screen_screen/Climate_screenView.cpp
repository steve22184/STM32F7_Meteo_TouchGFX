#include <gui/climate_screen_screen/Climate_screenView.hpp>

Climate_screenView::Climate_screenView() :
	yAngleT(0.0f),
	yAngleH(0.0f),
	deltaYangleT(0.029f),
	deltaYangleH(0.029f),
	old_mantissa(0),
	old_fraction(0),
	old_hum(0)
{
}

void Climate_screenView::setupScreen()
{
    Climate_screenViewBase::setupScreen();

    Unicode::snprintf(temp_nBuffer1, TEMP_NBUFFER1_SIZE, "%d", old_mantissa);
    Unicode::snprintf(temp_nBuffer2, TEMP_NBUFFER2_SIZE, "%d", old_fraction);

    Unicode::snprintf(hum_nBuffer, HUM_N_SIZE, "%d", old_hum);
}

void Climate_screenView::tearDownScreen()
{
    Climate_screenViewBase::tearDownScreen();
}

void Climate_screenView::handleTickEvent()
{
	yAngleT += deltaYangleT;
    yAngleH += deltaYangleH;

    temp.updateAngles(0, yAngleT, 0);
    hum.updateAngles(0, yAngleH, 0);

    uint16_t mantissa, fraction;

    if ( (mantissa = presenter->getTempMantissa()) != old_mantissa ||
    		(fraction = presenter->getTempFraction()) != old_fraction) {

    	old_mantissa = mantissa;
    	old_fraction = fraction;

    	Unicode::snprintf(temp_nBuffer1, TEMP_NBUFFER1_SIZE, "%d", mantissa);
    	Unicode::snprintf(temp_nBuffer2, TEMP_NBUFFER2_SIZE, "%d", fraction);

    	temp_n.invalidate();

    	temp_prg.setValue(mantissa);
    	temp_prg.invalidate();
    }


    uint8_t hum;
    if ( (hum = presenter->getHumidity()) != old_hum){

    	old_hum = hum;
    	Unicode::snprintf(hum_nBuffer, HUM_N_SIZE, "%d", hum);
    	hum_n.invalidate();

    	hum_prg.setValue(hum);
    	hum_prg.invalidate();
    }
}
