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

    if (!rockTexture.loadFromFile(TILES))
    {
        std::cout << "error loading tiles";
    }
    for (int i = 0; i < 8; i++)
    {
        rocks[i].setTexture(rockTexture);
        rocks[i].setTextureRect(sf::IntRect(0, 82, 180, 82));
        rocks[i].setScale(2,2);
    }
    rocks[0].setPosition(-50, WINDOW_HEIGHT-150);
    rocks[1].setPosition(275, WINDOW_HEIGHT - 150);
    rocks[2].setPosition(600, WINDOW_HEIGHT - 150);
    rocks[3].setPosition(925, WINDOW_HEIGHT - 150);
    rocks[4].setPosition(1250, WINDOW_HEIGHT - 150);
    rocks[5].setPosition(1575, WINDOW_HEIGHT - 150);
    rocks[6].setPosition(1900, WINDOW_HEIGHT - 150);
    rocks[7].setPosition(2225, WINDOW_HEIGHT - 150);
    

}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(back1);
    window.draw(back2);
    for (int i = 0; i < 8; i++)
    {
        window.draw(rocks[i]);
    }
    
}

void Background::update()
{
   move();
   moveRocks();
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

void Background::moveRocks()
{
    for (int i = 0; i < 8; i++)
    {
        rocks[i].move(-2.4, 0);
        if (rocks[i].getPosition().x < -375)
        {
            rocks[i].setPosition(2225, WINDOW_HEIGHT - 150);
        }
    }
    
}

void Background::increaseSpeed()
{
    speed = speed * 1.15;
}
