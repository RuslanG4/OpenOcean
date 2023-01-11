#include "Background.h"

Background::Background()
{
}

Background::Background(const char* t_texture, float t_speed, float t_scaleX,float t_scaleY, float t_width)
{
    if (!backT.loadFromFile(t_texture))
    {
        std::cout <<"error loading texting";
    }
    speed = t_speed;
    width = t_width;

    back1.setTexture(backT);
    back2.setTexture(backT);
    back1.setScale(t_scaleX, t_scaleY);
    back2.setScale(t_scaleX, t_scaleY);
    back2.setPosition(width, 0);;
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(back1);
    window.draw(back2);
}

void Background::update()
{
   move();
}

void Background::move()
{
    back1.move(-speed, 0);
    back2.move(-speed, 0);
    if (back1.getPosition().x<= -width)
    {
        back1.setPosition(width-10,0); //2 images looping to give off infinite feel, resets x position 
    }
    if (back2.getPosition().x<= -width)
    {
        back2.setPosition(width-10, 0);
    }
}

void Background::increaseSpeed()
{
    speed = speed * 1.15;
}
