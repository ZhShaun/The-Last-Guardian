#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
    al_destroy_bitmap(background);

    al_destroy_font(title_font);
    al_destroy_font(label_font);
    al_destroy_font(context_font);
}
