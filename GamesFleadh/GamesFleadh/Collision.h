#pragma once

#include<iostream>
#include<cmath>

class Rectangle{

private:
float x, y;

float width, height;
public:

Rectangle(float t_x, float t_y,float t_width,float t_height) :
x(t_x),y(t_y),width(t_width),height(t_height){};

/// @brief if two rectangles are intersecting return true
/// @param t_value 
/// @param t_x 
/// @param t_xPlusWidth 
/// @return 
bool valueInRange(float t_value, float t_x, float t_xPlusWidth)
{
    return(t_value>=t_x&&t_value<=t_xPlusWidth);
}

/// @brief determines whether AABB collision is occuring
/// @param b rect 2
/// @return true is collision
bool checkRectangleCollision(Rectangle*b)
{
    bool collisionX = valueInRange(x,b->x,b->x + b->width) || valueInRange(b->x,x,x+width);
    bool collisionY = valueInRange(y,b->y,b->y + b->height) || valueInRange(b->y,y,y+height);

    return collisionX && collisionY;
}

float getXpos() { return x; };
float getYpos() { return y; };

void setXpos(float t_x) { x=t_x; };
void setYpos(float t_y) { y=t_y; };


};

class Circle{

private:
float x, y;

float radius;
public:

Circle(float t_x,float t_y,float t_radius) :
 x(t_x), y(t_y),radius(t_radius){};

 /// @brief Finds in intersecting based on pythagarus theorum
/// @param b second circle
/// @return  true if colliding
bool checkCircleCollision(Circle* b)
{
    float gapX = x - b->x;
    float gapY = y - b->y;

    float length = sqrt((gapX*gapX) + (gapY*gapY));

    if(length<radius+b->radius)
    {
        return true;
    }
    return false;
}

};




