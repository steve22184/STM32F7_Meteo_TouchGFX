// Generated by imageconverter. Please, do not edit!

#ifndef BITMAPDATABASE_HPP
#define BITMAPDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/Bitmap.hpp>

const uint16_t BITMAP_BEADS_BKG_ID = 0;
const uint16_t BITMAP_BEIGE_NOTE_APP_ID = 1;
const uint16_t BITMAP_DARK_CLOCKS_BACKGROUNDS_CLOCK_STANDARD_BACKGROUND_ID = 2;
const uint16_t BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_HOUR_HAND_ID = 3;
const uint16_t BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_MINUTE_HAND_ID = 4;
const uint16_t BITMAP_DARK_CLOCKS_HANDS_CLOCK_STANDARD_SECOND_HAND_ID = 5;
const uint16_t BITMAP_GREEN_NOTE_APP_ID = 6;
const uint16_t BITMAP_HUM_APP_ID = 7;
const uint16_t BITMAP_PRG_CIRCLE_ID = 8;
const uint16_t BITMAP_SLIDER_BACKGROUND_ID = 9;
const uint16_t BITMAP_SLIDER_BACKGROUND_FILLED_ID = 10;
const uint16_t BITMAP_SLIDER_KNOB_CIRCLE_ID = 11;
const uint16_t BITMAP_TEMP_APP_ID = 12;
const uint16_t BITMAP_TGFX_LOGO_WHITE_ID = 13;

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance();
uint16_t getInstanceSize();
}

#endif
