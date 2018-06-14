#include "Tower.h"
#include "RangeAttack.h"
#include "global.h"

Tower::Tower(int pos_x, int pos_y, int r)
{
    this->attack_circle = new Circle(pos_x, pos_y, r);
}

Tower::~Tower()
{
    delete attack_circle;

    al_destroy_bitmap(img);
    al_destroy_bitmap(attack_img);

    for(auto&& child : this->attack_set) {
        delete child;
    }
    this->attack_set.clear();
}

void
Tower::Draw()
{
    int draw_x = attack_circle->x - (tower_width/2);
    int draw_y = attack_circle->y - (tower_height - (tower_width/2));

    al_draw_bitmap(img, draw_x, draw_y, 0);
    attack_counter = (attack_counter + 1) % attack_frequency;

    for(unsigned int i=0; i<this->attack_set.size(); i++)
    {
        this->attack_set[i]->Draw();
    }

    al_draw_filled_rectangle(attack_circle->x - (tower_width/2),
                             attack_circle->y - (tower_height - (tower_width/2),
                             attack_circle->x + (tower_width/2),
                             attack_circle->y + (tower_height - (tower_width/2),
                             al_map_rgb(255, 255, 255));
}

bool
Tower::DetectAttack()
{
    bool willAttack = false;
    RangeAttack *range_attack;

    if(Circle::isOverlap(this->circle, monster->getCircle()))
    {
        /*
        * TODO:
        *   Don't allow tower make new attack over and over again.
        *   Only when the counter reaches "0" can tower trigger new attack.
        *
        */
        if(attack_counter == 0)
        {
            range_attack = new Attack(
                this->circle,
                monster->getCircle(),
                this->attack_harm_point,
                this->attack_velocity,
                this->attack_img
            );

            this->attack_set.push_back(attack);
            willAttack = true;
        }
    }

    return willAttack;
}

bool
Tower::TriggerAttack(Monster *monster)
{
    bool isDestroyed = false;

    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), monster->getCircle()))
        {
            /*TODO:*/
            /*1. Reduce the army HP by the harm point*/
            /*2. Erase and delete the attack from attack_set*/
            /*3. Return true if the army's HP is reduced to zero*/
            isDestroyed = ->Subtract_HP(attack_harm_point);

            this->attack_set.erase(this->attack_set.begin() + i);
            delete(this->attack_set[i]);
            if(isDestroyed) break;
        }
    }
    return isDestroyed;
}

void
Tower::UpdateAttack()
{
    for(unsigned int i=0; i < this->attack_set.size(); i++)
    {
        if(!Circle::isOverlap(this->attack_set[i]->getCircle(), this->circle))
        {
            RangeAttack *range_attack = this->attack_set[i];

            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete range_attack;
        }
    }
}
