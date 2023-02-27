#include "Light.h"

Light::Light()
{
	
}

Light::Light(sf::Vector2f pos)
{
    center = pos;
    init();
}



void Light::init()
{
    triangle = sf::VertexArray(sf::TrianglesFan, 17);

    triangle[0].position = sf::Vector2f(center); //centre
    triangle[1].position = sf::Vector2f(center.x, center.y - 200);
    triangle[2].position = sf::Vector2f(center.x + 100, center.y - 200);
    triangle[3].position = sf::Vector2f(center.x+200, center.y - 100);
    triangle[4].position = sf::Vector2f(center.x + 200, center.y);
    triangle[5].position = sf::Vector2f(center.x + 200, center.y + 100);
    triangle[6].position = sf::Vector2f(center.x + 100, center.y + 200);
    triangle[7].position = sf::Vector2f(center.x, center.y + 200);
    triangle[8].position = sf::Vector2f(center.x-100, center.y + 200);
    triangle[9].position = sf::Vector2f(center.x - 200, center.y + 100);
    triangle[10].position = sf::Vector2f(center.x -200, center.y + 100);
    triangle[11].position = sf::Vector2f(center.x -200, center.y);
    triangle[12].position = sf::Vector2f(center.x -100, center.y);
    triangle[13].position = sf::Vector2f(center.x-200, center.y);
    triangle[14].position = sf::Vector2f(center.x-200, center.y-100);
    triangle[15].position = sf::Vector2f(center.x-100, center.y-200);
    triangle[16].position = sf::Vector2f(center.x, center.y - 200);

    // define the color of the triangle's points
    triangle[0].color = LightCenterColour;
    for (int i = 1; i < 17; i++)
    {
        triangle[i].color = lightOutgoingColour;
    }
}

void Light::scale(float t_x, float t_y)
{
    triangle[1].position = sf::Vector2f(center.x, center.y - 200 * t_y);
    triangle[2].position = sf::Vector2f(center.x + 100 * t_x, center.y - 200 * t_y);
    triangle[3].position = sf::Vector2f(center.x + 200 * t_x, center.y - 100 * t_y);
    triangle[4].position = sf::Vector2f(center.x + 200 * t_x, center.y);
    triangle[5].position = sf::Vector2f(center.x + 200 * t_x, center.y + 100 * t_y);
    triangle[6].position = sf::Vector2f(center.x + 100 * t_x, center.y + 200 * t_y);
    triangle[7].position = sf::Vector2f(center.x, center.y + 200 * t_y);
    triangle[8].position = sf::Vector2f(center.x - 100 * t_x, center.y + 200 * t_y);
    triangle[9].position = sf::Vector2f(center.x - 200 * t_x, center.y + 100 * t_y);
    triangle[10].position = sf::Vector2f(center.x - 200 * t_x, center.y + 100 * t_y);
    triangle[11].position = sf::Vector2f(center.x - 200 * t_x, center.y);
    triangle[12].position = sf::Vector2f(center.x - 100 * t_x, center.y);
    triangle[13].position = sf::Vector2f(center.x - 200 * t_x, center.y);
    triangle[14].position = sf::Vector2f(center.x - 200 * t_x, center.y - 100 * t_y);
    triangle[15].position = sf::Vector2f(center.x - 100 * t_x, center.y - 200 * t_y);
    triangle[16].position = sf::Vector2f(center.x, center.y - 200 * t_y);
}

void Light::setCenter(sf::Vector2f t_centre)
{
    center = t_centre;
    triangle[0].position = center;
}

void Light::setIntensity(float t_percent)
{
    lightIntensity = lightIntensity * t_percent;
    LightCenterColour = sf::Color(153, 255, 255, lightIntensity);
    triangle[0].color = LightCenterColour;

}

void Light::setMaxLight(float t_lightAmount)
{
    lightIntensity = t_lightAmount;
}

void Light::moveLight(float a, float b)
{
    for (int i = 0; i < 17; i++)
    {
        triangle[i].position.x += a;
        triangle[i].position.y += b;
    }
}

void Light::followCentre(sf::Vector2f t_pos)
{
    center = t_pos;

    triangle[0].position = sf::Vector2f(center); //centre
    triangle[1].position = sf::Vector2f(center.x, center.y - 200);
    triangle[2].position = sf::Vector2f(center.x + 100, center.y - 200);
    triangle[3].position = sf::Vector2f(center.x + 200, center.y - 100);
    triangle[4].position = sf::Vector2f(center.x + 200, center.y);
    triangle[5].position = sf::Vector2f(center.x + 200, center.y + 100);
    triangle[6].position = sf::Vector2f(center.x + 100, center.y + 200);
    triangle[7].position = sf::Vector2f(center.x, center.y + 200);
    triangle[8].position = sf::Vector2f(center.x - 100, center.y + 200);
    triangle[9].position = sf::Vector2f(center.x - 200, center.y + 100);
    triangle[10].position = sf::Vector2f(center.x - 200, center.y + 100);
    triangle[11].position = sf::Vector2f(center.x - 200, center.y);
    triangle[12].position = sf::Vector2f(center.x - 100, center.y);
    triangle[13].position = sf::Vector2f(center.x - 200, center.y);
    triangle[14].position = sf::Vector2f(center.x - 200, center.y - 100);
    triangle[15].position = sf::Vector2f(center.x - 100, center.y - 200);
    triangle[16].position = sf::Vector2f(center.x, center.y - 200);
}
