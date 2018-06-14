#include "StartScene.h"

StartScene::StartScene()
{
    background = al_load_bitmap("./image/StartScene/Background.png");

    title_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", context_font_size, 0);

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 255, 255);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 255, 255);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 255, 255);
}

StartScene::~StartScene()
{

}

void StartScene::SceneInit()
{
    cout << "Start scene initializing...\n";

    title_x = (window_width - title_width)/2;
    title_y = title_top;

    start_label_x = (window_width - start_label_width)/2;
    start_label_y = title_y + title_height + label_difference * 10;

    select_label_x = (window_width - select_label_width)/2;
    select_label_y = start_label_y + start_label_height + label_difference * 3;

    setting_label_x = (window_width - setting_label_width)/2;
    setting_label_y = select_label_y + select_label_height + label_difference * 3;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = setting_label_y + setting_label_height + label_difference * 3;

    cout << "Start scene drawing...\n";
}

void StartScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "The Last Guardian");

    //al_draw_filled_rectangle(start_label_x, start_label_y, start_label_x + start_label_width, start_label_y + start_label_height, label_color);
    al_draw_text(label_font, label_text_color, start_label_x + start_label_width/2, start_label_y, ALLEGRO_ALIGN_CENTRE, "Start");

    //al_draw_filled_rectangle(select_label_x, select_label_y, select_label_x + select_label_width, select_label_y + select_label_height, label_color);
    al_draw_text(label_font, label_text_color, select_label_x + select_label_width/2, select_label_y, ALLEGRO_ALIGN_CENTRE, "Select");

    //al_draw_filled_rectangle(setting_label_x, setting_label_y, setting_label_x + setting_label_width, setting_label_y + setting_label_height, label_color);
    al_draw_text(label_font, label_text_color, setting_label_x + setting_label_width/2, setting_label_y, ALLEGRO_ALIGN_CENTRE, "Setting");

    //al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, label_color);
    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "Exit");

    al_flip_display();
}

int StartScene::LabelSelected(int pos_x, int pos_y)
{
    if(pos_x >= start_label_x && pos_x <= start_label_x + start_label_width && pos_y >= start_label_y && pos_y <= start_label_y + start_label_height)
    {
        return GAME_BEGIN;
    }
    else if(pos_x >= select_label_x && pos_x <= select_label_x + select_label_width && pos_y >= select_label_y && pos_y <= select_label_y + select_label_height)
    {
        return GAME_SELECT;
    }
    else if(pos_x >= setting_label_x && pos_x <= setting_label_x + setting_label_width && pos_y >= setting_label_y && pos_y <= setting_label_y + setting_label_height)
    {
        return GAME_SETTING;
    }
    else if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        return GAME_EXIT;
    }
    else
    {
        return GAME_INIT;
    }
}
