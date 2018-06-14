#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "global.h"

typedef struct Node {
    int h, g, f;
    bool roadPoint;
}Node;

class Map {
public:
    Map(const int);
    ~Map();

    void setMap(const int);

    int getMap() { return maps; }
    //void search_destination();
    std::vector<int> ReturnObject() { return MapObject_type; }

    int ArmyNum[minion_num];

private:
    Node ground[NumOfGrid];
    std::vector<int> MapObject_type;
    // current level number
    int maps = 1;
};


#endif // LEVEL_H_INCLUDED
