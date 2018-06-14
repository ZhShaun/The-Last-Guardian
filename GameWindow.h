#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "Menu.h"
#include "Map.h"
#include "RangeAttack.h"
#include "Slider.h"
#include "global.h"
#include "StartScene.h"
#include "SettingScene.h"
#include "SelectScene.h"
#include "PauseScene.h"
#include "ResultScene.h"
#include "ExitScene.h"

const float FPS = 60;

const int HolyWaterSpeed = FPS * 2;
const int HolyWater_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // destructor
    ~GameWindow();

    // debug usage
    void show_error_message(string msg);

    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);

    // game control function
    void game_init();
    void game_begin();
    void game_play();
    void game_reset();
    void game_destroy();

    // draw running animation
    int draw_running_animation();

    // game update
    int game_update();

    // game scene
    int game_start_scene(StartScene*);
    int game_setting_scene(SettingScene*);
    int game_select_scene(SelectScene*);
    int game_run_scene();
    int game_pause_scene(PauseScene*);
    int game_result_scene(ResultScene*);
    int game_exit_scene(ExitScene*);

    // game process of update event
    int process_event_start_scene(StartScene*);
    int process_event_setting_scene(SettingScene*);
    int process_event_select_scene(SelectScene*);
    int process_event_run_scene();
    int process_event_pause_scene(PauseScene*);
    int process_event_result_scene(ResultScene*);
    int process_event_exit_scene(ExitScene*);

    // game volume variable
    static float background_volume;
    static float effect_volume;

    // game control variable
    bool redraw = false;
    bool mute = false;
    bool pause = false;
    bool initial = true;

private:
    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_BITMAP* icon;
    ALLEGRO_BITMAP* background = NULL;

    ALLEGRO_FONT* Small_font = NULL;
    ALLEGRO_FONT* Medium_font = NULL;
    ALLEGRO_FONT* Large_font = NULL;

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;

    ALLEGRO_TIMER* timer = NULL;

    ALLEGRO_SAMPLE* sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE* start_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE* background_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE* result_sound = NULL;

    Map *maps = NULL;
    Menu *menu = NULL;

    // mouse axes
    float mouse_x, mouse_y;
};


#endif // MAINWINDOW_H_INCLUDED
