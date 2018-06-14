#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include "Object.h"
#include "RangeAttack.h"
#include "Circle.h"
#include "Monster.h"
#include "global.h"

class Tower : public Object
{
public:
    Tower(int, int, int);
    ~Tower();

    // override virtual function "Object::Draw"
    void Draw();
    void resetAttackCounter() { attack_counter = 0; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    void UpdateAttack();
    // detect if tower needs to attack some monster
    bool DetectAttack();
    // process if some of attack in set touches monster
    bool TriggerAttack();

    int getWidth() { return tower_width; }
    int getHeight() { return tower_height; }
    int getHP() { return Tower_HP; }

    bool Subtract_HP(int);

protected:
    // setting of attack
    int attack_frequency;
    int attack_counter;
    int attack_harm_point;
    int attack_velocity;
    int Tower_HP;
    int tower_width;
    int tower_height;
    ALLEGRO_BITMAP *attack_img;
    std::vector<Attack*> attack_set;

    // information of tower
    ALLEGRO_BITMAP *img;
};

#endif // TOWER_H_INCLUDED
