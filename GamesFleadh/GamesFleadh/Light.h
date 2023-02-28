#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Light
{
private:
	sf::VertexArray triangle;
	sf::Vector2f center{0,0};

	float lightIntensity = 76.5; //30%

	sf::Color LightCenterColour = sf::Color(153, 255, 255, lightIntensity);
	sf::Color lightOutgoingColour = sf::Color(153, 255, 255, 1);

	
public:
	Light();
	Light(sf::Vector2f pos);

	sf::VertexArray draw() { return triangle; };

	void init();

	void scale(float t_x, float t_y);
	void setCenter(sf::Vector2f t_centre);

	void setIntensity(float t_percent);
	void setMaxLight(float t_lightAmount);
	void moveLight(float a, float b);

	void followCentre(sf::Vector2f t_pos);

	void selectColour(sf::Color t_colour, sf::Color t_colourLight);

};

