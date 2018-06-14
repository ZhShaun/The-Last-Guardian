#include "SettingScene.h"

SettingScene::SettingScene()
{
    background = al_load_bitmap("./image/SettingScene/Background.png");

    title_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", context_font_size, 0);

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 255, 255);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 255, 255);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 255, 255);

    back_sound = new Slider((window_width - 100)/2, 100 + label_difference * 10);
    effect_sound = new Slider((window_width - 100)/2, 100 + label_difference * 15);
}

SettingScene::~SettingScene()
{
    delete back_sound;
    delete effect_sound;
}

void SettingScene::SceneInit()
{
    cout << "Setting scene initializing...\n";

    title_x = (window_width - title_width)/2;
    title_y = title_top;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = setting_label_y + setting_label_height + label_difference * 3;

    back_sound->set_label_content("BACKGROUND SOUND");

    back_sound->set_color(al_map_rgb(255, 255, 255));

    effect_sound->set_label_content("EFFECT SOUND");

    effect_sound->set_color(al_map_rgb(255, 255, 255));
}

void SettingScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    back_sound->Draw();

    effect_sound->Draw();

    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "SETTING");

    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "RETURN");

    al_flip_display();
}

int SettingScene::LabelSelected(int pos_x, int pos_y)
{
    if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        return GAME_BACK;
    }
    else
    {
        return GAME_SETTING;
    }
}
