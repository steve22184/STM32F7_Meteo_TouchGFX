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

protected:

private:

    float xAngleTGFX;
    float yAngleTGFX;
    float zAngleTGFX;

    float deltaXangleTGFX;
    float deltaYangleTGFX;
    float deltaZangleTGFX;
};

#endif // MAINVIEW_HPP
