#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/mainViewBase.hpp>
#include <gui/main_screen/mainPresenter.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>


class mainView : public mainViewBase
{
public:
    mainView();
    virtual ~mainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    virtual void hplusClicked();
    virtual void hminusClicked();
    virtual void mplusClicked();
    virtual void mminusClicked();
    virtual void setupClicked();
protected:

private:

    float xAngleTGFX;
    float yAngleTGFX;
    float zAngleTGFX;

    float yAngleT;
    float yAngleH;

    float deltaXangleTGFX;
    float deltaYangleTGFX;
    float deltaZangleTGFX;

    float deltaYangleT;
    float deltaYangleH;

    uint8_t hour, minute, second;
};

#endif // MAINVIEW_HPP
