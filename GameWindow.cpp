#include "GameWindow.h"

// constructor and destructor
GameWindow::GameWindow()
{
    if(!al_init())
    {
        show_error_message("Game initialization fail.");
    }

    cout << "Game initializing...\n";

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    if(display == NULL)
    {
        show_error_message("Game display creation fail.");
    }
    if(event_queue == NULL)
    {
        show_error_message("Game event_queue creation fail.");
    }
    if(timer == NULL)
    {
        show_error_message("Game timer creation fail.");
    }

    al_init_acodec_addon();     // initialize acodec addon
    al_init_font_addon();       // initialize the font addon
    al_init_image_addon();      // initialize the image addon
    al_init_primitives_addon(); // initialize the primitive addon
    al_init_ttf_addon();        // initialize the ttf addon

    al_install_audio();    // install audio event
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event

    Small_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0);  // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); // load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0);  // load large font

    if(Small_font == NULL || Medium_font == NULL || Large_font == NULL)
    {
        show_error_message("Game font loading fail.");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initializing the resources
    game_init();
}

GameWindow::~GameWindow()
{

}
// end of constructor and destructor

// debug usage
void
GameWindow::show_error_message(string msg)
{
    cout << msg << endl;

    game_destroy();
    exit(9);
}
// end of debug usage

// detect if mouse hovers over a rectangle
bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
    {
        if(mouse_y >= starty && mouse_y <= starty + height)
        {
            return true;
        }
    }

    return false;
}
// end of detect if mouse hovers over a rectangle

// game control function
void
GameWindow::game_init()
{
    srand(time(NULL));

    icon = al_load_bitmap("./image/Icon.png");
    background = al_load_bitmap("./image/RunScene/Background.png");

    if(icon == NULL || background == NULL)
    {
        show_error_message("Game run scene images loading fail.");
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("./sound/RunScene/StartSound.ogg");
    start_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(start_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(start_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/RunScene/BackgroundSound.ogg");
    background_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(background_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(background_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/RunScene/ResultSound.ogg");
    result_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(result_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(result_sound, al_get_default_mixer());

    if(start_sound == NULL || background == NULL || result_sound == NULL)
    {
        show_error_message("Game run scene sounds loading fail.");
    }
}

void
GameWindow::game_begin()
{
    cout << "Game start.";

    draw_running_animation();

    al_play_sample_instance(start_sound);
    while(al_get_sample_instance_playing(start_sound))
    {
        al_play_sample_instance(background_sound);
    }

    al_start_timer(timer);
}

void
GameWindow::game_play()
{
    int msg = -1;

    StartScene* start_scene = new StartScene();
    SettingScene* setting_scene = new SettingScene();
    SelectScene* select_scene = new SelectScene();
    PauseScene* pause_scene = new PauseScene();
    ResultScene* result_scene = new ResultScene();
    ExitScene* exit_scene = new ExitScene();

    while(msg != GAME_EXIT)
    {
        switch(msg)
        {
            case GAME_INIT:
                msg = game_start_scene(start_scene);
                break;
            case GAME_SETTING:
                msg = game_setting_scene(setting_scene);
                break;
            case GAME_SELECT:
                msg = game_select_scene(select_scene);
                break;
            case GAME_BEGIN:
                game_begin();
                msg = GAME_CONTINUE;
                break;
            case GAME_CONTINUE:
                msg = game_run_scene();
                break;
            case GAME_PAUSE:
                msg = game_pause_scene(pause_scene);
                break;
            case GAME_RESULT:
                msg = game_result_scene(result_scene);
                break;
            /*case GAME_EXIT:
                msg = game_exit_scene(exit_scene);
                break;*/
        }
    }
    /*
    delete start_scene;
    delete setting_scene;
    delete select_scene;
    delete pause_scene;
    delete result_scene;
    delete exit_scene;
    */
    show_error_message("Game terminate.");
}

void
GameWindow::game_reset()
{
    redraw = false;
    mute = false;
    pause = false;

    // stop sample instance
    al_stop_sample_instance(start_sound);
    al_stop_sample_instance(background_sound);
    al_stop_sample_instance(result_sound);

    // stop timer
    al_stop_timer(timer);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_font(Small_font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_event_queue(event_queue);

    al_destroy_timer(timer);

    al_destroy_sample(sample);
    al_destroy_sample_instance(start_sound);
    al_destroy_sample_instance(background_sound);
    al_destroy_sample_instance(result_sound);
}
// end of game control function

// draw running animation
int
GameWindow::draw_running_animation()
{

}
// end of draw running animation

// game update
int
GameWindow::game_update()
{

}
// end of game update

// game scene
int
GameWindow::game_start_scene(StartScene* start_scene)
{
    int msg = GAME_INIT;

    if(!start_scene->get_initial())
    {
        start_scene->SceneInit();
        start_scene->toggle_initial();
    }
    start_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_start_scene(start_scene);
    }
    return msg;
}

int
GameWindow::game_setting_scene(SettingScene* setting_scene)
{
    int msg = GAME_SETTING;

    setting_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_setting_scene(setting_scene);
    }
    return msg;
}

int
GameWindow::game_select_scene(SelectScene* select_scene)
{
    int msg = GAME_SELECT;

    select_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_select_scene(select_scene);
    }
    return msg;
}

int
GameWindow::game_run_scene()
{
    int msg = GAME_CONTINUE;

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_run_scene();
    }
    return msg;
}

int
GameWindow::game_pause_scene(PauseScene* pause_scene)
{
    int msg = GAME_PAUSE;

    pause_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_pause_scene(pause_scene);
    }
    return msg;
}

int
GameWindow::game_result_scene(ResultScene* result_scene)
{
    int msg = GAME_RESULT;

    result_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_result_scene(result_scene);
    }
    return msg;
}

int
GameWindow::game_exit_scene(ExitScene* exit_scene)
{
    int msg = GAME_EXIT;

    exit_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_exit_scene(exit_scene);
    }
    return msg;
}
// end of game scene

// game process of update event
int
GameWindow::process_event_start_scene(StartScene* start_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        return start_scene->LabelSelected(mouse_x, mouse_y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    return GAME_INIT;
}

int
GameWindow::process_event_setting_scene(SettingScene* setting_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(setting_scene->back_sound->isClicked(mouse_x, mouse_y))
            {
                setting_scene->back_sound->toggleDrag();
            }
            else if(setting_scene->effect_sound->isClicked(mouse_x, mouse_y))
            {
                setting_scene->effect_sound->toggleDrag();
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            if(setting_scene->back_sound->isDragged())
            {
                setting_scene->back_sound->toggleDrag();
            }
            else if(setting_scene->effect_sound->isDragged())
            {
                setting_scene->effect_sound->toggleDrag();
            }

            return setting_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(setting_scene->back_sound->isDragged())
        {
            al_set_sample_instance_gain(backgroundSound, setting_scene->back_sound->Drag(mouse_x, mouse_y));
        }
        else if(setting_scene->effect_sound->isDragged())
        {
            al_set_sample_instance_gain(effectSound, setting_scene->effect_sound->Drag(mouse_x, mouse_y));
        }
    }

    return GAME_SETTING;
}

int
GameWindow::process_event_select_scene(SelectScene* select_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        return select_scene->LabelSelected(mouse_x, mouse_y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    return GAME_SELECT;
}

int
GameWindow::process_event_run_scene()
{

}

int
GameWindow::process_event_pause_scene(PauseScene* pause_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        return pause_scene->LabelSelected(mouse_x, mouse_y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    return GAME_PAUSE;
}

int
GameWindow::process_event_result_scene(ResultScene* result_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        return result_scene->LabelSelected(mouse_x, mouse_y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    return GAME_RESULT;
}

int
GameWindow::process_event_exit_scene(ExitScene* exit_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        return exit_scene->LabelSelected(mouse_x, mouse_y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    return GAME_EXIT;
}
// end of game process of update event
