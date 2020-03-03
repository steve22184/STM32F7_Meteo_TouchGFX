#include <gui/main_screen/mainView.hpp>

mainView::mainView() :

	xAngleTGFX(0.0f),
	yAngleTGFX(0.0f),
	zAngleTGFX(0.0f),

	deltaXangleTGFX(0.032f),
	deltaYangleTGFX(0.029f),
	deltaZangleTGFX(0.027f)
	{

	}

void mainView::setupScreen()
{
    mainViewBase::setupScreen();
    tgfx_slider.setValue(presenter->getSliderValue());
}

void mainView::tearDownScreen()
{
    mainViewBase::tearDownScreen();
    presenter->setSliderValue(tgfx_slider.getValue());
}

void mainView::handleTickEvent()
{
    // Update angle values

    xAngleTGFX += deltaXangleTGFX;
    yAngleTGFX += deltaYangleTGFX;
    zAngleTGFX += deltaZangleTGFX;

    // Update the images with the new angles
    // The image is automatically invalidated (the optimal minimal area).
    // If any of the set..() methods (e.g. setOrigo, setCamera, setRenderingAlgorithm...) are used
    // remember to manually invalidate the image afterwards (textureMapperImage2D.invalidate()).

    tgfx.updateAngles(xAngleTGFX, yAngleTGFX, zAngleTGFX);
}


