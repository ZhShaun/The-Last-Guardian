#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Object.h"
#include "Circle.h"
#include "global.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30, offsetY = 150;

class Menu : public Object
{
public:
    Menu();
    ~Menu();

    void Reset();
    void Draw();

    // Check if current coin is not less than needed coin
    bool Enough_HolyWater(int);
    void Change_HolyWater(int change) { HolyWater += change; }

    bool isInRange(int point, int startPos, int length);

    int selected(int area);

    int getArmyHolyWater(int type) { return need_HolyWater[type]; }
    int getHolyWater() { return HolyWater; }

    int menu_random[4];

private:
    std::vector<ALLEGRO_BITMAP*> menu_army;

    ALLEGRO_FONT *menuFont;
    int HolyWater = 0;
    int selectedArmy = -1;
    int need_HolyWater[minion_num] = {};
};

#endif // MENU_H_INCLUDED
