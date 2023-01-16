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
	enableGestures();

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

	for (int i = 0; i < currentEnemies; i++)
	{
		fish[i]->update(player->getPosition());
		bigFish[i]->update(player->getPosition());
		longFish[i]->update(player->getPosition());
		mine[i]->update(player->getPosition());
	}	

	player->update();
	player->handleInput(input);

	if (!gameOver)
	{
		if (!player->getAlive())
		{
			gameOver = true;

		}

		myPlant->update();

		myOverLay.getOxyLevel(player->getOxyLvl());
		myOverLay.update();

	//	FSM();

		bg1->update();
		bg2->update();

		pearlReset();

		damage();
		fishColl();
		pearlCollision();
		increaseEnemies();

		checkHand(controller);
	}
	else
	{
		input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
		gameOverScreen.getDistance(myOverLay.returnDistance());
		gameOverScreen.update();
		if (gameOverScreen.getRestart())
		{
			deleteEntities();
			restartGame();
			gameOverScreen.setRestartFalse();
			gameOver = false;
		}
	}

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
	myOverLay.render(m_window);
	m_window.draw(player->getAnimatedSpriteFrame());
	m_window.draw(m_bubbles);

	
	myPlant->render(m_window);
	

	if (gameOver)
	{
		gameOverScreen.render(m_window);
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		std::cout << "error";
	}
	if (!m_ArialBlackfont.loadFromFile(FONT))
	{
		std::cout << "error loading font";
	}
	myOverLay.initialise(m_ArialBlackfont);
	if (!m_bubblesTexture.loadFromFile(BUBBLES))
	{
		std::cout << "error loading bubbles";
	}
	m_bubbles.setTexture(m_bubblesTexture);
	m_bubbles.setScale(3, 3);
	m_bubbles.setTextureRect(sf::IntRect(0, 0, 23, 40));

	player_animated_sprite = AnimatedSprite(player_texture);
	player = new Player(player_animated_sprite);

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

	myPlant = new Plant;
	myPlant->initialise();
	
	myOverLay.initialise(m_ArialBlackfont);
	gameOverScreen.initialise(m_ArialBlackfont);
}

void Game::animateBubbles()
{
	m_bubbles.setPosition(player->getAnimatedSpriteFrame().getPosition().x-30, player->getAnimatedSpriteFrame().getPosition().y-100);
	bubbleTimer++;
	if (bubbleTimer > 6)
	{
		bubbleFrame++;
		if (bubbleFrame >= 4) //frame 44 is the last frame the robot is running
		{
			bubbleFrame = 0; //37 is the first frame the robot is running
			
		}
		bubbleTimer = 0;
	}
	int col = bubbleFrame % 4; //total cols is 5
	int row = 0; //

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 40;
	rectSourceSprite.width = 23;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_bubbles.setTextureRect(rectSourceSprite);
}

void Game::FSM()
{
	if (!damaged)
	{
		input.setCurrent(gpp::Events::Event::SWIM_RIGHT_START_EVENT);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			input.setCurrent(gpp::Events::Event::SWIM_FAST);
		}
		if (player->vectorLengthSquared() < 0.25)
		{
			input.setCurrent(gpp::Events::Event::SWIM_RIGHT_STOP_EVENT);
			player->hit();
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
			player->hit();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(bigFish[i]->CollisionBox()) && !immune)
		{
			if (bigFish[i]->isChasing())
			{
				input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
				player->killPlayer();
			}
			else
			{
				input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
				player->hit();
				damaged = true;
				immune = true;
			}
		}
		if (player->CollisionBox()->checkRectangleCollision(longFish[i]->CollisionBox()) && !immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->hit();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(mine[i]->CollisionBox()) &&!immune)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->mineHit();
			mine[i]->setDamageT();
			damaged = true;
			immune = true;
		}
	}
}

void Game::increaseEnemies()
{
	if (clock.getElapsedTime().asSeconds() > 40.f)
	{
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
		animateBubbles();
		tumble++;
		if (tumble > 30)
		{
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN_STOP);
			player->setVelBack();
		}
		if (tumble > 42)
		{
			tumble = 0;
			damaged = false;

		}
	}
	immuneTimer++;
	if (immuneTimer > 100)
	{
		immune = false;
		immuneTimer = 0;
	}
	if (!damaged)
	{
		m_bubbles.setPosition(-100, -100);
	}
}

void Game::enableGestures()
{
	controller.addListener(listener);

	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
	controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
}

int Game::detectGestures(Leap::Frame frame)
{
	Leap::GestureList gestures = frame.gestures();

	for (int i = 0; i < gestures.count(); i++)
	{
		Leap::Gesture gesture = gestures[i];
		switch (gesture.type())
			{
		case Leap::Gesture::TYPE_CIRCLE:
			return 1;
			break;
		case Leap::Gesture::TYPE_KEY_TAP:
			
			break;
		case Leap::Gesture::TYPE_SWIPE:
			break;
		case Leap::Gesture::TYPE_SCREEN_TAP:
			
			break;
		}
	}
	return-1;

}

void Game::checkHand(Leap::Controller controller)
{
	const Leap::Frame frame = controller.frame();
	int i = detectGestures(frame);
	std::string handType = handCheck(controller);

	if (!damaged)
	{
		input.setCurrent(gpp::Events::Event::SWIM_RIGHT_START_EVENT);

		if (i == 1 && handType == "Left hand")
		{
			input.setCurrent(gpp::Events::Event::SWIM_FAST);
			player->moveLEAP(std::string("left-hand"));
			
		}
		else if (i == 1 && handType == "Right hand")
		{
			input.setCurrent(gpp::Events::Event::SWIM_FAST);
			player->moveLEAP(std::string("right-hand"));
			
		}
		if (player->vectorLengthSquared() < 0.25)
		{
			input.setCurrent(gpp::Events::Event::SWIM_RIGHT_STOP_EVENT);
			player->hit();
		}
		if (frame.fingers().extended().count() > 8)
		{
			player->moveLEAP(std::string("fingers"));
		}
		if (frame.fingers().extended().count() < 7)
		{
			player->moveLEAP(std::string("fingersDown"));
		}
	}
}


std::string Game::handCheck(Leap::Controller controller)
{
	const Leap::Frame frame = controller.frame();
	std::string handType;

	Leap::HandList hands = frame.hands();
	for (Leap::HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl)
	{
		// Get the first hand
		const Leap::Hand hand = *hl;
		handType = hand.isLeft() ? "Left hand" : "Right hand";

		return handType;
	}
	
}

void Game::deleteEntities()
{
	delete player;
	delete bg1;
	delete bg2;
	for (int i = 0; i < currentEnemies; i++)
	{
		delete fish[i];
		delete bigFish[i];
		delete longFish[i];
		delete mine[i];
	}

	delete myPlant;

}

void Game::restartGame()
{
	myOverLay.reset();

	input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN_STOP);

	currentEnemies = 1;
	tumble = 0;
	immuneTimer = 0;
	damaged = false;
	immune = false;

	player = new Player(player_animated_sprite);

	bg1 = new Background(BG_, 3.4, 2, 2, 1350);
	bg2 = new Background(BG_ROCKS, 3.8, 2, 2, 1920);

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

	myPlant = new Plant;
	myPlant->initialise();
	

}

void Game::pearlReset()
{
	if (myPlant->plantPos().x < -100)
	{
		myPlant->setPosition();
	}
}

void Game::pearlCollision()
{

	if (player->CollisionBox()->checkRectangleCollision(myPlant->CollisionBox()))
	{
		myPlant->bubbleSetPos();
		player->bubblesHit();
	}

}
