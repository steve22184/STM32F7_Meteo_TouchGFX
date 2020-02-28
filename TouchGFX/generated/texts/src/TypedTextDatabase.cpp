/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <touchgfx/TypedText.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

extern touchgfx::GeneratedFont& getFont_verdana_20_4bpp();
extern touchgfx::GeneratedFont& getFont_verdana_40_4bpp();
extern touchgfx::GeneratedFont& getFont_verdana_10_4bpp();
extern touchgfx::GeneratedFont& getFont_segoesc_30_4bpp();
extern touchgfx::GeneratedFont& getFont_ITCBLKAD_TTF_25_4bpp();
extern touchgfx::GeneratedFont& getFont_ITCBLKAD_TTF_16_4bpp();

const touchgfx::Font* _fonts[] =
{
    &(getFont_verdana_20_4bpp()),
    &(getFont_verdana_40_4bpp()),
    &(getFont_verdana_10_4bpp()),
    &(getFont_segoesc_30_4bpp()),
    &(getFont_ITCBLKAD_TTF_25_4bpp()),
    &(getFont_ITCBLKAD_TTF_16_4bpp())
};

extern const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[];
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 4, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 5, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 5, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR }
};

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    typedText_database_DEFAULT
};

namespace TypedTextDatabase
{
const touchgfx::TypedText::TypedTextData* getInstance(touchgfx::LanguageId id)
{
    return typedTextDatabaseArray[id];
}

uint16_t getInstanceSize()
{
    return sizeof(typedText_database_DEFAULT) / sizeof(touchgfx::TypedText::TypedTextData);
}

const touchgfx::Font** getFonts()
{
    return _fonts;
}

const touchgfx::Font* setFont(touchgfx::FontId fontId, const touchgfx::Font* font)
{
    const touchgfx::Font* old = _fonts[fontId];
    _fonts[fontId] = font;
    return old;
}

void resetFont(touchgfx::FontId fontId)
{
    switch (fontId)
    {
    case 0:
        _fonts[0] = &(getFont_verdana_20_4bpp());
        break;
    case 1:
        _fonts[1] = &(getFont_verdana_40_4bpp());
        break;
    case 2:
        _fonts[2] = &(getFont_verdana_10_4bpp());
        break;
    case 3:
        _fonts[3] = &(getFont_segoesc_30_4bpp());
        break;
    case 4:
        _fonts[4] = &(getFont_ITCBLKAD_TTF_25_4bpp());
        break;
    case 5:
        _fonts[5] = &(getFont_ITCBLKAD_TTF_16_4bpp());
        break;
    }
}
}  // namespace TypedTextDatabase
