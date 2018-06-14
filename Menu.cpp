#include "Menu.h"

Menu::Menu()
{
    char filename[50];

    HolyWater = 0;

    for(int i=0;i<minion_num; i++)
    {
        ALLEGRO_BITMAP *minion;
        sprintf(filename, "./minion/%s_Menu.png", ArmyClass[i]);

        minion = al_load_bitmap(filename);
        menu_tower.push_back(minion);
    }

    menuFont = al_load_ttf_font("pirulen.ttf", 12, 0); // load font
}

Menu::~Menu()
{
    al_destroy_font(menuFont);

    for(int i=0; i < minion_num; i++)
        al_destroy_bitmap(menu_army[i]);

    menu_army.clear();
}

void
Menu::Reset()
{
    HolyWater = 0;
}

void
Menu::Draw()
{
    for(int i = 0; i < 4; i++)
    {
        menu_random[i] = rand()&10;
        ALLEGRO_BITMAP *tem = menu_army[menu_random[i]];

        int pos_x = offsetX;
        int pos_y = offsetY + (ThumbHeight + gapY) * i;

        al_draw_bitmap(tem, pos_x, pos_y, 0);

        if(!Enough_HolyWater())
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgba(100, 100, 100, 100));
        else if(i == selectedArmy)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
    }
}

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;

    return false;
}

int
Menu::selected(int area)
{
    selectedArmy = -1;

    for(int i = 0; i < 4; i++)
    {
        int pos_x = offsetX;
        int pos_y = offsetY + (ThumbHeight + gapY) * i;

        if(isInRange(area, pos_x, ThumbWidth) && isInRange(area, pos_y, ThumbHeight))
        {
            if(Enough_HolyWater(i))
            {
                selectedArmy = i;
                break;
            }
        }
    }

    return selectedArmy;
}

bool
Menu::Enough_HolyWater(int type)
{

    if(type < 0 || type >= minion_num)
        return false;

    return (HolyWater + need_HolyWater[type] >= 0);
}
