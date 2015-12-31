//collideBox.cpp
//PA
//12/6/15

#include "collideBox.h"

using namespace std;

collideBox::collideBox()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

collideBox::collideBox(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

int collideBox::getX1()
{
    return x1;
}

int collideBox::getX2()
{
    return x2;
}

int collideBox::getY1()
{
    return y1;
}

int collideBox::getY2()
{
    return y2;
}

void collideBox::update(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}
