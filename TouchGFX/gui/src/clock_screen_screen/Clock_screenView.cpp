#include <gui/clock_screen_screen/Clock_screenView.hpp>

Clock_screenView::Clock_screenView():
	hour(0),
	minute(0),
	second(0)
	{
	}

void Clock_screenView::setupScreen()
{
    Clock_screenViewBase::setupScreen();

    watch.setTime24Hour(presenter->getHour(), presenter->getMinute(), presenter->getSecond());

    clock_set.setX(presenter->getClockSetX());
    clock_set.setY(presenter->getClockSetY());

    quote.setX(presenter->getQuoteX());
    quote.setY(presenter->getQuoteY());

    presenter->readNewQuote();
}

void Clock_screenView::handleTickEvent()
{
	watch.setTime24Hour(presenter->getHour(), presenter->getMinute(), presenter->getSecond());

	if ( presenter->getQuotesFlag() ){
		Unicode::strncpy(quote_txtBuffer, (const char*)presenter->getQuotes(), QUOTE_TXT_SIZE);
		quote_txt.setWideTextAction(WIDE_TEXT_WORDWRAP);
		quote_txt.invalidate();
	}
}

void Clock_screenView::tearDownScreen()
{
    Clock_screenViewBase::tearDownScreen();

    presenter->setQuoteX(quote.getX());
    presenter->setQuoteY(quote.getY());

    presenter->setClockSetX(clock_set.getX());
    presenter->setClockSetY(clock_set.getY());
}

void Clock_screenView::hplusClicked(){
	hour == 23 ? hour = 0 : ++hour;
	Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%d", hour);
	hour_n.invalidate();
}
void Clock_screenView::hminusClicked(){
	hour == 0 ? hour = 23 : --hour;
	Unicode::snprintf(hour_nBuffer, HOUR_N_SIZE, "%d", hour);
	hour_n.invalidate();
}
void Clock_screenView::mplusClicked(){
	minute == 59 ? minute = 0 : ++minute;
	Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%d", minute);
	minute_n.invalidate();
}
void Clock_screenView::mminusClicked(){
	minute == 0 ? minute = 59 : --minute;
	Unicode::snprintf(minute_nBuffer, MINUTE_N_SIZE, "%d", minute);
	minute_n.invalidate();
}
void Clock_screenView::setupClicked(){
	presenter->saveHour(hour+1);
	presenter->saveMinute(minute);

	presenter->setSetupFlag();
}
