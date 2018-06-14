#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

class Circle{
public:
    Circle() {}

    Circle(int x, int y, int r)
    {
        this->x = x;
        this->y = y;
        this->r = r;
    }

    static bool isOverlap(Circle*, Circle*);

    int r;
    int x, y;
};

#endif // CIRCLE_H_INCLUDED
