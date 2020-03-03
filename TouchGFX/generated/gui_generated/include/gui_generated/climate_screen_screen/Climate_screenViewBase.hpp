/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CLIMATE_SCREENVIEWBASE_HPP
#define CLIMATE_SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/climate_screen_screen/Climate_screenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Climate_screenViewBase : public touchgfx::View<Climate_screenPresenter>
{
public:
    Climate_screenViewBase();
    virtual ~Climate_screenViewBase() {}
    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image climate_bkg;
    touchgfx::Container climate;
    touchgfx::Image beige_note;
    touchgfx::AnimationTextureMapper temp;
    touchgfx::CircleProgress temp_prg;
    touchgfx::PainterRGB565 temp_prgPainter;
    touchgfx::TextAreaWithTwoWildcards temp_n;
    touchgfx::Image green_note;
    touchgfx::AnimationTextureMapper hum;
    touchgfx::CircleProgress hum_prg;
    touchgfx::PainterRGB565 hum_prgPainter;
    touchgfx::TextAreaWithOneWildcard hum_n;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEMP_NBUFFER1_SIZE = 5;
    touchgfx::Unicode::UnicodeChar temp_nBuffer1[TEMP_NBUFFER1_SIZE];
    static const uint16_t TEMP_NBUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar temp_nBuffer2[TEMP_NBUFFER2_SIZE];
    static const uint16_t HUM_N_SIZE = 5;
    touchgfx::Unicode::UnicodeChar hum_nBuffer[HUM_N_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // CLIMATE_SCREENVIEWBASE_HPP
