/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/clock_screen_screen/Clock_screenViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Clock_screenViewBase::Clock_screenViewBase() :
    flexButtonCallback(this, &Clock_screenViewBase::flexButtonCallbackHandler),
    clock_set_outEndedCallback(this, &Clock_screenViewBase::clock_set_outEndedCallbackHandler)
{

    clock_bkg.setXY(0, 0);
    clock_bkg.setBitmap(touchgfx::Bitmap(BITMAP_BEADS_BKG_ID));

    clock.setPosition(0, 0, 480, 320);

    watch.setXY(22, 39);
    watch.setBackground(BITMAP_DARK_CLOCKS_BACKGROUNDS_CLOCK_STANDARD_BACKGROUND_ID, 116, 116);
    watch.setupSecondHand(BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_SECOND_HAND_ID, 3, 66);
    watch.setupMinuteHand(BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_MINUTE_HAND_ID, 7, 67);
    watch.setMinuteHandSecondCorrection(false);
    watch.setupHourHand(BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_HOUR_HAND_ID, 7, 52);
    watch.setHourHandMinuteCorrection(false);
    watch.initializeTime24Hour(9, 1, 5);
    watch.setAnimation(30, touchgfx::EasingEquations::bounceEaseOut);
    clock.add(watch);

    clock_set.setPosition(270, 45, 200, 230);

    box2.setPosition(0, 0, 200, 230);
    box2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    box2.setAlpha(128);
    clock_set.add(box2);

    hour.setPosition(60, 16, 80, 25);
    hour.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    hour.setLinespacing(0);
    hour.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));
    clock_set.add(hour);

    hour_n.setPosition(60, 41, 80, 45);
    hour_n.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    hour_n.setLinespacing(0);
    Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID3).getText());
    hour_n.setWildcard(hour_nBuffer);
    hour_n.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));
    clock_set.add(hour_n);

    minute.setPosition(60, 111, 80, 25);
    minute.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    minute.setLinespacing(0);
    minute.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));
    clock_set.add(minute);

    minute_n.setPosition(60, 136, 80, 45);
    minute_n.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    minute_n.setLinespacing(0);
    Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID5).getText());
    minute_n.setWildcard(minute_nBuffer);
    minute_n.setTypedText(touchgfx::TypedText(T_SINGLEUSEID4));
    clock_set.add(minute_n);

    setup.setText(TypedText(T_SINGLEUSEID10));
    setup.setTextPosition(0, 0, 80, 25);
    setup.setTextColors(touchgfx::Color::getColorFrom24BitRGB(10, 10, 10), touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    setup.setPosition(60, 194, 80, 25);
    setup.setAction(flexButtonCallback);
    clock_set.add(setup);

    hplus.setText(TypedText(T_SINGLEUSEID6));
    hplus.setTextPosition(0, 0, 25, 25);
    hplus.setTextColors(touchgfx::Color::getColorFrom24BitRGB(10, 10, 10), touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    hplus.setPosition(21, 29, 25, 25);
    hplus.setAction(flexButtonCallback);
    clock_set.add(hplus);

    hminus.setText(TypedText(T_SINGLEUSEID19));
    hminus.setTextPosition(0, 0, 25, 25);
    hminus.setTextColors(touchgfx::Color::getColorFrom24BitRGB(10, 10, 10), touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    hminus.setPosition(21, 63, 25, 25);
    hminus.setAction(flexButtonCallback);
    clock_set.add(hminus);

    mplus.setText(TypedText(T_SINGLEUSEID8));
    mplus.setTextPosition(0, 0, 25, 25);
    mplus.setTextColors(touchgfx::Color::getColorFrom24BitRGB(10, 10, 10), touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    mplus.setPosition(21, 123, 25, 25);
    mplus.setAction(flexButtonCallback);
    clock_set.add(mplus);

    mminus.setText(TypedText(T_SINGLEUSEID9));
    mminus.setTextPosition(0, 0, 25, 25);
    mminus.setTextColors(touchgfx::Color::getColorFrom24BitRGB(10, 10, 10), touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    mminus.setPosition(21, 158, 25, 25);
    mminus.setAction(flexButtonCallback);
    clock_set.add(mminus);
    clock.add(clock_set);

    quote.setPosition(270, -230, 200, 230);

    box1.setPosition(0, 0, 200, 200);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    box1.setAlpha(128);
    quote.add(box1);

    quote_txt.setPosition(0, 41, 200, 159);
    quote_txt.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    quote_txt.setLinespacing(0);
    quote_txtBuffer[0] = 0;
    quote_txt.setWildcard(quote_txtBuffer);
    quote_txt.setTypedText(touchgfx::TypedText(T_SINGLEUSEID20));
    quote.add(quote_txt);

    quote_h.setPosition(0, 1, 200, 40);
    quote_h.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    quote_h.setLinespacing(0);
    quote_h.setTypedText(touchgfx::TypedText(T_SINGLEUSEID11));
    quote.add(quote_h);

    btn_pen.setBitmaps(Bitmap(BITMAP_PEN_APP_ID), Bitmap(BITMAP_PEN_APP_ID));
    btn_pen.setBitmapXY(0, 0);
    btn_pen.setPosition(170, 144, 30, 56);
    quote.add(btn_pen);
    clock.add(quote);

    add(clock_bkg);
    add(clock);
}

void Clock_screenViewBase::setupScreen()
{

}

//Handles when a key is pressed
void Clock_screenViewBase::handleKeyEvent(uint8_t key)
{
    if(2 == key)
    {
        //Clock_to_climate
        //When hardware button 2 clicked change screen to Climate_screen
        //Go to Climate_screen with screen transition towards North
        application().gotoClimate_screenScreenSlideTransitionNorth();
    }
    if(14 == key)
    {
        //btn_pen_Interaction
        //When hardware button 14 clicked execute C++ code
        //Execute C++ code
        presenter->readNewQuote();
    }
}

void Clock_screenViewBase::clock_set_outEndedCallbackHandler(const touchgfx::MoveAnimator<touchgfx::Container>& comp)
{

}

void Clock_screenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &setup)
    {
        //setupInteraction
        //When setup clicked call virtual function
        //Call setupClicked
        setupClicked();

        //clock_set_out
        //When setupInteraction completed move clock_set
        //Move clock_set to x:270, y:-230 with LinearIn easing in 50 ms (3 Ticks)
        clock_set.clearMoveAnimationEndedAction();
        clock_set.startMoveAnimation(270, -230, 3, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
        clock_set.setMoveAnimationEndedAction(clock_set_outEndedCallback);

        //quote_in
        //When setupInteraction completed move quote
        //Move quote to x:270, y:45 with LinearIn easing in 50 ms (3 Ticks)
        quote.clearMoveAnimationEndedAction();
        quote.startMoveAnimation(270, 45, 3, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
    }
    else if (&src == &hplus)
    {
        //hplusInteraction
        //When hplus clicked call virtual function
        //Call hplusClicked
        hplusClicked();
    }
    else if (&src == &hminus)
    {
        //hminusInteraction
        //When hminus clicked call virtual function
        //Call hminusClicked
        hminusClicked();
    }
    else if (&src == &mplus)
    {
        //mplusInteraction
        //When mplus clicked call virtual function
        //Call mplusClicked
        mplusClicked();
    }
    else if (&src == &mminus)
    {
        //mminusInteraction
        //When mminus clicked call virtual function
        //Call mminusClicked
        mminusClicked();
    }
}