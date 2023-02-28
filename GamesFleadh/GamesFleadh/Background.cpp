#include "Background.h"

Background::Background()
{
}

Background::Background(const char* t_texture, float t_speed, float t_scaleX,float t_scaleY, float t_width, bool t_light)
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


    if (!totemT.loadFromFile(TOTEM))
    {
        std::cout << "error loading totem";
    }
    totem.setTexture(totemT);
    totem.setScale(2,2);
    totem.setPosition(rand()%1920, rand() % 100 + 575);
    totem.setColor(sf::Color(195, 184, 184));


    if (!platT.loadFromFile(PLATFORM))
    {
        std::cout << "error loading PLATFORM";
    }
    platform.setTexture(platT);
    platform.setScale(2, 2);
    platform.setPosition(rand() % 1920, rand() % 300 + 375);
    platform.setColor(sf::Color(195, 184, 184));
    
    platLight = Light{ sf::Vector2f(30,03) };

    platLight.setMaxLight(255);
    platLight.setIntensity(0.6);
    platLight.selectColour(sf::Color(0,0, 0), sf::Color(128, 128, 128));

    if (t_light)
    {
        bgLight = true;

        light[0] = Light{sf::Vector2f(300,120)};
        light[1] = Light{ sf::Vector2f(1350,120) };
        light[2] = Light{ sf::Vector2f(800,800) };

        light[3] = Light{ sf::Vector2f(width+300,120) };
        light[4] = Light{ sf::Vector2f(width + 1350,120) };
        light[5] = Light{ sf::Vector2f(width + 800,800) };
        for (int i = 0; i < numLight; i++)
        {
            light[i].setMaxLight(255);
            light[i].setIntensity(0.5);
            light[i].scale(2, 2);
        }
        light[0].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
        light[1].selectColour(sf::Color(51, 255, 255), sf::Color(153, 255, 255));
        light[2].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));

        light[3].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
        light[5].selectColour(sf::Color(153, 51, 255), sf::Color(204, 153, 255));
        light[4].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
    }

}

Background::Background(float t_scaleX, float t_scaleY, float t_x, float t_y, const char* t_texture)
{
    if (!backT.loadFromFile(t_texture))
    {
        std::cout << "error loading texting";
    }
    yCo = t_y;
    xCo = t_x;
    plant.setTexture(backT);
    plant.setScale(t_scaleX, t_scaleY);
    plant.setOrigin(32, 64);
    plant.setPosition(xCo, yCo);
    speed = 0;
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(back1);
    window.draw(back2);
    window.draw(totem);
    window.draw(platLight.draw());
    if (bgLight)
    {
        for (int i = 0; i < numLight; i++)
        {
            window.draw(light[i].draw());
        }
    }
   
    window.draw(platform);
    
    
    for (int i = 0; i < 8; i++)
    {
        window.draw(rocks[i]);
    }
   
    
}

void Background::update()
{
   move();
   moveRocks();
   moveOtherBG();
}

void Background::move()
{
    back1.move(-speed, 0);
    back2.move(-speed, 0);
    if (back1.getPosition().x<= -width)
    {
        back1.setPosition(width-10,0); //2 images looping to give off infinite feel, resets x position 
        if (bgLight)
        {
            light[0] = Light{ sf::Vector2f(width + 300,120) };
            light[1] = Light{ sf::Vector2f(width + 1350,120) };
            light[2] = Light{ sf::Vector2f(width + 800,800) };
            for (int i = 0; i < 3; i++)
            {
                light[i].setMaxLight(255);
                light[i].setIntensity(0.5);
                light[i].scale(2, 2);
            }
            light[0].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
            light[1].selectColour(sf::Color(51, 255, 255), sf::Color(153, 255, 255));
            light[2].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));


        }
    }
    if (back2.getPosition().x<= -width)
    {
        back2.setPosition(width-10, 0);
        light[3] = Light{ sf::Vector2f(width + 300,120) };
        light[4] = Light{ sf::Vector2f(width + 1350,120) };
        light[5] = Light{ sf::Vector2f(width + 800,800) };
        for (int i = 3; i < numLight; i++)
        {
            light[i].setMaxLight(255);
            light[i].setIntensity(0.5);
            light[i].scale(2, 2);
        }
        light[3].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
        light[5].selectColour(sf::Color(153, 51, 255), sf::Color(204, 153, 255));
        light[4].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
    }
    if (bgLight)
    {
        for (int i = 0; i < numLight; i++)
        {
            
            light[i].moveLight(-speed, 0);
        }
    }
 
}

void Background::moveRocks()
{
    for (int i = 0; i < 8; i++)
    {
        rocks[i].move(-3.6, 0);
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

void Background::moveOtherBG()
{
    platform.move(-speed, 0);
    totem.move(-speed, 0);
    if (totem.getPosition().x < -500)
    {
        totem.setPosition(rand() % 500 + 1920, rand()%100 + 575);
    }
    if (platform.getPosition().x < -500)
    {
        platform.setPosition(rand() % 500 + 1920, rand() % 300 + 375);
    }

    platLight.followCentre(sf::Vector2f(platform.getPosition().x + 250, platform.getPosition().y+150));

}

void Background::drawPlants(sf::RenderWindow& window)
{
    window.draw(plant);
}

void Background::updatePlants()
{
    plant.move(-3.6, 0);
    if (plant.getPosition().x < -400)
    {
        plant.setPosition(rand() % 500 + 1920, yCo);
    }
}

