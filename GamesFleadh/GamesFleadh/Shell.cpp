#include "Shell.h"

Shell::Shell()
{
	init();
}

void Shell::init()
{
	if (!m_shellTexture.loadFromFile(SHELL))
	{
		std::cout << "error loading SHELL";
	}

	m_shell.setTexture(m_shellTexture);
	m_shell.setPosition((rand()% 400 + 100)+WINDOW_WIDTH, rand()%900 + 100);
	m_shell.setOrigin(21, 15);

	light = Light{ sf::Vector2f(m_shell.getPosition()) };
	light.scale(0.15, 0.15);
	light.setMaxLight(100);
	light.selectColour(sf::Color(0, 153, 153), sf::Color(204, 255, 255));

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);

	if (!font.loadFromFile(FONT))
	{
		std::cout << "error loading font";
	}
	m_text.setFont(font);
	m_text.setCharacterSize(40U);
	m_text.setString("25");
	m_text.setPosition(-400, 400);
	m_text.setFillColor(sf::Color(255, 227, 248, 255));
}

void Shell::render(sf::RenderWindow& window)
{
	window.draw(light.draw());
	window.draw(m_shell);
	//window.draw(m_box);
	window.draw(m_text);
}

void Shell::update()
{
	light.followCentre(m_shell.getPosition());
	light.scale(0.15, 0.15);

	m_shell.rotate(3);
	move();
	updateHB();

	if (startMove)
	{
		moveText();
	}
}


void Shell::updateHB()
{
	
	m_box.setPosition(m_shell.getPosition().x-21, m_shell.getPosition().y-15);
	shellHB = new Rectangle(m_box.getPosition().x , m_box.getPosition().y, 42, 30);
}

void Shell::move()
{
	m_shell.setPosition(sf::Vector2f(m_shell.getPosition().x, m_shell.getPosition().y + -(float)std::cos(m_shell.getPosition().x / 200) * 2));
	m_shell.move(-7, 0);

	if (m_shell.getPosition().x < -50)
	{
		m_shell.setPosition(sf::Vector2f(rand() % 400 + 100 + WINDOW_WIDTH, rand() % 900 + 100));
	}
}

void Shell::setText()
{
	startMove = true;
	m_text.setPosition(m_shell.getPosition());
	soundPlay();
}

void Shell::moveText()
{
	m_text.move(-2.4, -3.4);


	if (m_text.getPosition().y < -50)
	{
		m_text.setPosition(1300, 1080);
		startMove = false;
	}
}

void Shell::respawn()
{
	m_shell.setPosition(sf::Vector2f(rand() % 400 + 100 + WINDOW_WIDTH, rand() % 900 + 100));
}

void Shell::soundPlay()
{

	if (!pop.openFromFile("ASSETS\\AUDIO\\shellPickUp.wav"))
	{
		std::cout << "error laoding music";
	}

	pop.setVolume(15);
	pop.play();
}
