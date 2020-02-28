/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/TypedText.hpp>
#include <texts/TypedTextDatabase.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/TextProvider.hpp>

touchgfx::Font::StringWidthFunctionPointer touchgfx::Font::getStringWidthFunction = &touchgfx::Font::getStringWidthLTR;
touchgfx::LCD::DrawStringFunctionPointer touchgfx::LCD::drawStringFunction = &touchgfx::LCD::drawStringLTR;
touchgfx::TextProvider::UnicodeConverterInitFunctionPointer touchgfx::TextProvider::unicodeConverterInitFunction = static_cast<touchgfx::TextProvider::UnicodeConverterInitFunctionPointer>(0);
touchgfx::TextProvider::UnicodeConverterFunctionPointer touchgfx::TextProvider::unicodeConverterFunction = static_cast<touchgfx::TextProvider::UnicodeConverterFunctionPointer>(0);

//Default typed text database
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    0x42, 0x6f, 0x74, 0x68, 0x20, 0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 0x73, 0x74, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x70, 0x65, 0x73, 0x73, 0x69, 0x6d, 0x69, 0x73, 0x74, 0x73, 0x20, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x74, 0x6f, 0x20, 0x73, 0x6f, 0x63, 0x69, 0x65, 0x74, 0x79, 0x2e, 0x20, 0x54, 0x68, 0x65, 0x20, 0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 0x73, 0x74, 0x20, 0x69, 0x6e, 0x76, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x74, 0x68, 0x65, 0x20, 0x61, 0x65, 0x72, 0x6f, 0x70, 0x6c, 0x61, 0x6e, 0x65, 0x2c, 0x20, 0x74, 0x68, 0x65, 0x20, 0x70, 0x65, 0x73, 0x73, 0x69, 0x6d, 0x69, 0x73, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x70, 0x61, 0x72, 0x61, 0x63, 0x68, 0x75, 0x74, 0x65, 0x2e, 0x2, 0x0, // @0 "Both optimists and pessimists contribute to society. The optimist invents the aeroplane, the pessimist the parachute.<>"
    0x51, 0x75, 0x6f, 0x74, 0x65, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x64, 0x61, 0x79, 0x0, // @119 "Quote of the day"
    0x2, 0xb0, 0x43, 0x0, // @136 "<>?C"
    0x2, 0x25, 0x0, // @140 "<>%"
    0x4d, 0x69, 0x6e, 0x75, 0x74, 0x65, 0x0, // @143 "Minute"
    0x53, 0x45, 0x54, 0x55, 0x50, 0x0, // @150 "SETUP"
    0x51, 0x75, 0x6f, 0x74, 0x65, 0x0, // @156 "Quote"
    0x48, 0x6f, 0x75, 0x72, 0x0, // @162 "Hour"
    0x30, 0x30, 0x0, // @167 "00"
    0x2d, 0x0, // @170 "-"
    0x2b, 0x0 // @172 "+"
};
extern uint32_t const indicesGb[];

//array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

//Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] =
{
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            //dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            //compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}

