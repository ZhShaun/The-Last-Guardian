#include "GameWindow.h"

using namespace std;

int main()
{
    GameWindow *The_Last_Guardian = new GameWindow();
    The_Last_Guardian->game_play();

    delete The_Last_Guardian;

    return 0;
}
