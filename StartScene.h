#ifndef STARTSCENE_H_INCLUDED
#define STARTSCENE_H_INCLUDED

#include "Window.h"

#define title_top 50
#define label_difference 10

#define title_font_size 50
#define label_font_size 30
#define context_font_size 20

class StartScene : public Window
{
public:
    StartScene();
    ~StartScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(int, int) override;

private:
    int title_x, title_y;
    int title_width = 450, title_height = 50;
    int start_label_x, start_label_y;
    int start_label_width = 100, start_label_height = 30;
    int select_label_x, select_label_y;
    int select_label_width = 100, select_label_height = 30;
    int setting_label_x, setting_label_y;
    int setting_label_width = 100, setting_label_height = 30;
    int exit_label_x, exit_label_y;
    int exit_label_width = 100, exit_label_height = 30;
};

#endif // STARTSCENE_H_INCLUDED
