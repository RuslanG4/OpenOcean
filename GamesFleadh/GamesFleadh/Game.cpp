#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText();

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}

/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed mouse
		{
			processMouse(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyRelease(newEvent);
		}
	}
}
/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouse(sf::Event t_event)
{
}

void Game::processKeyRelease(sf::Event t_event)
{

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	FSM();
	player->handleInput(input);
	player->update();

	for (int i = 0; i < currentEnemies; i++)
	{
		fish[i]->update();
		bigFish[i]->update();
		longFish[i]->update();
		mine[i]->update();
	}
	damage();
	fishColl();
	increaseEnemies();

	bg1->update();
	bg2->update();

}
/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	bg1->draw(m_window);
	bg2->draw(m_window);
	player->render(m_window);
	for (int i = 0; i < currentEnemies; i++)
	{
		fish[i]->render(m_window);
		bigFish[i]->render(m_window);
		longFish[i]->render(m_window);
		mine[i]->render(m_window);
	}

	m_window.draw(player->getAnimatedSpriteFrame());
	m_window.display();
}

void Game::setupFontAndText()
{
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		std::cout << "error";
	}

	player_animated_sprite = AnimatedSprite(player_texture);
	player = new Player(player_animated_sprite);
	player->getAnimatedSpriteFrame().setScale(2, 2);

	bg1 = new Background(BG_, 3.4,2,2,1350);
	bg2 = new Background(BG_ROCKS, 3.8,2,2,1920);

	for (int i = 0; i < 5; i++)
	{
		fish[i] = new Fish();
		fish[i]->loadTextures();

		bigFish[i] = new BigFish();
		bigFish[i]->loadTextures();

		longFish[i] = new LongFish();
		longFish[i]->loadTextures();

		mine[i] = new Mine();
		mine[i]->loadTextures();
	}
}

void Game::FSM()
{
	if (!damaged)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			input.setCurrent(gpp::Events::Event::SWIM_RIGHT_START_EVENT);
			player->makeIsMoveT();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			input.setCurrent(gpp::Events::Event::SWIM_RIGHT_START_EVENT);
			player->makeIsMoveT();
		}
		if (player->vectorLengthSquared() < 0.25)
		{
			input.setCurrent(gpp::Events::Event::SWIM_RIGHT_STOP_EVENT);
			player->makeIsMoveF();
		}
	}

}

void Game::fishColl()
{
	for (int i = 0; i < currentEnemies; i++)
	{
		if (player->CollisionBox()->checkRectangleCollision(fish[i]->CollisionBox()) && !immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->makeIsMoveF();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(bigFish[i]->CollisionBox()) && !immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->makeIsMoveF();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(longFish[i]->CollisionBox()) && !immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->makeIsMoveF();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(mine[i]->CollisionBox()) && !immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->makeIsMoveF();
			mine[i]->setDamageT();
			damaged = true;
			immune = true;
		}
	}
}

void Game::increaseEnemies()
{
	if (clock.getElapsedTime().asSeconds() > 20.f)
	{
		std::cout << "CLOCK";
		currentEnemies++;
		if (currentEnemies >= 5)
		{
			currentEnemies = 5;
		}
		clock.restart();
	}
}

void Game::damage()
{
	if (damaged)
	{
		tumble++;
		if (tumble > 42)
		{
			tumble = 0;
			damaged = false;
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN_STOP);
		}
	}
	immuneTimer++;
	if (immuneTimer > 90)
	{
		immune = false;
		immuneTimer = 0;
	}
}

