#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <math.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
#define abs(a) ((a > 0) ? (a) : (-a))
#define UPPER_BRIDGE 1
#define LOWER_BRIDGE 2
#define HEADING_TO_BRIDGE 1
#define PASSING_BRIDGE 2
#define HEADING_TO_TOWER 3

enum {LEFT=0, RIGHT, UP, DOWN};
enum {red_team = 0, blue_team};

class Minion : public Object
{
public:
    Minion(int posx, int posy);
    ~Minion();

    void Draw();
    virtual void find_way();
    virtual bool Move(); // return false if stop, including attack

    virtual void LoadAnimation() = 0;
    virtual void LoadAttackAnimation() = 0;


    bool DetectAttack();
    virtual bool TriggerAttack() = 0;
    virtual void UpdateAttack() = 0;

    int getHP() { return HealthPoint; }
    int getCost() { return cost; }
    int getTeam() { return team; }
    int getPathStage() { return path_stage; }
    int getIsAttack() { return is_attack; }

    void setSpeed(double rate) { speed *= rate; }
    void setCost(double rate) { cost *= rate; }
    void setTeam(int manipulate) { team = manipulate; }

    int findClosestTower(int, int); // return true if success

    bool Substract_HP(int harm);

protected:
    int team = red_team;
    int type; // which unit, referring global.h
    int dir_sprite[4]; // numbers of the pictures of each directions
    int HealthPoint = 20;
    int speed = 1;
    int cost = 5;
    char name[20];
private:
    // direction and index for "path"
    int cur_direction;
    bool is_attack;

    // animation counter
    int counter;

    int cur_sprite;

    int path_stage;
    double unit_heading_x;
    double unit_heading_y;

    int closest_tower_x;
    int closest_tower_y;
    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;

    std::vector<ALLEGRO_BITMAP*> attackImg;

    // feel the need to redesign attack class

} ;

#endif // MINION_H_INCLUDED
