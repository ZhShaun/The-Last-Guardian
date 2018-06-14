#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include "Object.h"
#include "Circle.h"
#include "global.h"

class Attack : public Object
{
public:
    Attack(Circle*, Circle*, int, int, ALLEGRO_BITMAP*);
    ~Attack();

    // override virtual function "Object::Draw"
    void Draw();
    int getHarmPoint() { return harm_point; }

    static float volume;

protected:
    ALLEGRO_BITMAP *attack_img;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *arrow = NULL;

private:
    int attack_velocity = 8;
    int harm_point = 5;
    float pos_x, pos_y;
    float direction_x, direction_y;
};

#endif // ATTACK_H_INCLUDED
