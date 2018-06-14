#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//GAME STATUS
#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_PAUSE 4
#define GAME_RESULT 5
#define GAME_RESET 6
#define GAME_EXIT 7
#define GAME_TERMINATE 8
#define GAME_BACK 9

#define window_width 1200
#define window_height 600

#define grid_width 20
#define grid_height 20

#define arena_field_width 500
#define arena_field_height 500
#define NumOfGrid (arena_field_width / grid_width) * (arena_field_height / grid_height)

#define minion_num 30

string ArmyClass[30] = {};

#endif
