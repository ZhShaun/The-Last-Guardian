#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Circle.h"

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;

    int getAttackX() { return attack_circle->x; }
    int getAttackY() { return attack_circle->y; }
    int getAttackRadius() { return attack_circle->r; }

    int getDetectX() { return detect_circle->x; }
    int getDetectY() { return detect_circle->y; }
    int getDetectRadius() { return detect_circle->r; }

    Circle* getAttackCircle() const { return attack_circle; }
    Circle* getDetectCircle() const { return detect_circle; }
protected:
    Circle *attack_circle;
    Circle *detect_circle;
};

#endif // OBJECT_H_INCLUDED
