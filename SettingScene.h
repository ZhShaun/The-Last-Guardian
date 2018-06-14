#ifndef SETTINGSCENE_H_INCLUDED
#define SETTINGSCENE_H_INCLUDED

#include "Window.h"

#define title_top 50
#define label_difference 10

#define title_font_size 35
#define label_font_size 25
#define context_font_size 20

class SettingScene : public Window
{
public:
    SettingScene();
    ~SettingScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(int, int) override;

    Slider *back_sound;
    Slider *effect_sound;

private:
    int title_x, title_y;
    int title_width = 450, title_height = 50;

    int exit_label_x, exit_label_y;
    int exit_label_width = 100, exit_label_height = 30;
};

#endif // SETTINGSCENE_H_INCLUDED
