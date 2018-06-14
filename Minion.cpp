#include "Minion.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
// for reading pictures, i.e. name/direction_name_xx.png
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Minion::Minion(int posx, int posy)
{
    // default direction
    if (this->team = red_team)
        direction = RIGHT;
    else if (this->team = blue_team)
        direction = LEFT;

    attack_circle = new Circle(posx, posy);
    detect_circle = new Circle(posx, posy);
    // attack_circle and detect_circle should be overrode

    // dir_sprite should be overrode

    // name should be overrode
    strncpy(name, "Default", 30);

    cur_sprite = 0;
    counter = 0;
}

Minion::~Minion()
{
    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP *img = moveImg[i];

        moveImg.erase(moveImg.begin() + i);

        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();

    delete circle;
}

void
Minion::Draw()
{
    int w, h;
    int offset = 0;

    // calculate the number of pictures before current direction
    for(int i=0; i<direction; i++)
        offset += dir_sprite[i];

    if(!moveImg[offset + cur_sprite])
        return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + cur_sprite]);
    h = al_get_bitmap_height(moveImg[offset + cur_sprite]);


    // draw bitmap align grid edge
    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w/2, circle->y - (h - grid_height/2), 0);

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}

void
Minion::find_way() // to find the values of unit_heading_x and unit_heading_y
{
    double path_x, path_y, path_length;

    if (type == AIR_UNIT)
        path_stage = HEADING_TO_TOWER;

    switch (getPathStage)
    {
        case HEADING_TO_BRIDGE:
            int heading_bridge;

            if (team == red_team)
                path_x = (double) (window_width / 2 - RIVER_WIDTH / 2) - circle->x;
            else if (team == blue_team)
                path_x = (double) (window_width / 2 + RIVER_WIDTH / 2) - circle->x;

            heading_bridge = (abs(UPPER_BRIDGE_Y - circle->y) > abs(LOWER_BRIDGE_Y - circle->y))
                                ? UPPER_BRIDGE : LOWER_BRIDGE;

            if (heading_bridge == UPPER_BRIDGE)
                path_y = (double) UPPER_BRIDGE_Y - circle->y;
            else if (heading_bridge == LOWER_BRIDGE)
                path_y = (double) LOWER_BRIDGE_Y - circle->y;

            unit_heading_x = (double) path_x / path_length;
            unit_heading_y = (double) path_y / path_length;
            break;
        case PASSING_BRIDGE:
            if (team == red_team)
                unit_heading_x = 1;
            else if (team == blue_team)
                unit_heading_x = -1;
            unit_heading_y = 0;
            break;
        case HEADING_TO_TOWER:
            path_x = (double) closest_tower_x - circle->x;
            path_y = (double) closest_tower_y - circle->y;
            path_length = sqrt(path_x*path_x + path_y*path_y);

            unit_heading_x = (double) path_x / path_length;
            unit_heading_y = (double) path_y / path_length;
            break;
        default:
            cout << "Error occurs !!" << endl;
    }

    if (unit_heading_y == 0)
    {
        if (unit_heading_x > 0)
            cur_direction = RIGHT;
        else if (unit_heading_x < 0)
            cur_direction = LEFT;
    }
    else
    {
        double rate = (double) unit_heading_x / unit_heading_y;

        if (unit_heading_x >= 0)
        {
            if (rate<=1 && rate>=-1)
                cur_direction = RIGHT;
            else if (rate > 1)
                cur_direction = UP;
            else if (rate < 1)
                cur_direction = DOWN;
        }
        else
        {
            if (rate<=1 && rate>=-1)
                cur_direction = LEFT;
            else if (rate > 1)
                cur_direction = DOWN;
            else if (rate < 1)
                cur_direction = UP;
        }
    }

}

void
Minion:: findClosestTower(int tower_x, int tower_y)
{
    closest_tower_x = tower_x;
    closest_tower_y = tower_y;
}

bool
Minion:: Move() //
{
    static int prev_direction = LEFT;

    counter = (counter + 1) % draw_frequency;

    if (!getIsAttack())
    {
        prev_direction = cur_direction;
        if (counter == 0)
            cur_sprite = (cur_sprite + 1) % dir_sprite[cur_direction];
        // attack sprite++
    }

    if (prev_direction != cur_direction)
        cur_sprite = 0;

    circle->x += speed * unit_heading_x;
    circle->y += speed * unit_heading_y;

}
