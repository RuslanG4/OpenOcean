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
	playBG();
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
	if (state == gameState::SPLASH)
	{
		splash.update();
		updateSplashClock();
	}
	if (state == gameState::GAMEPLAY)
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

			squidControl();

			myPlant->update();
			myChest->update();
			myChest->checkCollision(player);

			myOverLay.getOxyLevel(player->getOxyLvl(), player->getPearls());
			myOverLay.update();

			bg1->update();
			bg2->update();

			for (int i = 0; i < 4; i++)
			{
				seabush[i]->updatePlants();
				kelp[i]->updatePlants();
			}

			plantReset();

			damage();
			fishColl();
			plantBubbleCollision();
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

}
/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(DEEPGREEN);

	if (state == gameState::SPLASH)
	{
		splash.render(m_window);
	}
	if (state == gameState::GAMEPLAY)
	{

		bg1->draw(m_window);
		if (!bossFight)
		{
			m_window.draw(squid.getLight().draw());
			m_window.draw(squid.getBsquid());
		}
		bg2->draw(m_window);
		for (int i = 0; i < 4; i++)
		{
			kelp[i]->drawPlants(m_window);
			seabush[i]->drawPlants(m_window);
		}
		m_window.draw(darkness);



		for (int i = 0; i < currentEnemies; i++)
		{
			fish[i]->render(m_window);
			bigFish[i]->render(m_window);
			longFish[i]->render(m_window);
			mine[i]->render(m_window);
		}
		if (bossFight)
		{
			squid.render(m_window);
		}


		m_window.draw(m_bubbles);





		myPlant->render(m_window);
		myChest->render(m_window);

		player->render(m_window);
		m_window.draw(player->getAnimatedSpriteFrame());

		myOverLay.render(m_window);

		if (gameOver)
		{
			bgMusic.stop();
			gameOverScreen.render(m_window);
		}
	}

	m_window.display();
}
/// <summary>
/// SET UP AND INITIALISATION
/// </summary>
void Game::setupFontAndText()
{
	splash.initialise();

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

	bg1 = new Background(BG_, 2.4, 3, 3, 2000);
	bg2 = new Background(BG_ROCKS, 3, 2, 2, 1920);

	for (int i = 0; i < 4; i++)
	{
		kelp[i] = new Background(2, 2, rand() % 1920, WINDOW_HEIGHT - 50, KELP);
		seabush[i] = new Background(2, 2, rand() % 1920, WINDOW_HEIGHT - 50, SEABUSH);
	}

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

	myChest = new Chest();
	myChest->initialise();

	squid.loadTextures();
	
	myOverLay.initialise(m_ArialBlackfont);
	gameOverScreen.initialise(m_ArialBlackfont);


	darkness.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	darkness.setFillColor(sf::Color((255, 255, 255, 108)));
	darkness.setPosition(0, 0);

}
/// <summary>
/// timer for splash Screen
/// </summary>
void Game::updateSplashClock()
{
	if (splashClock.getElapsedTime().asSeconds() > 3.3f)
	{
		state = gameState::GAMEPLAY;
	};
}
/// <summary>
/// ANIMATES THE BUBBLES THAT APPEAR WHEN PLAYER IS HIT
/// </summary>
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
/// <summary>
/// CHECKS ALL COLLISION BOXES
/// </summary>
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
			mine[i]->sound();
			input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN);
			player->mineHit();
			mine[i]->setDamageT();
			damaged = true;
			immune = true;
		}
		if (player->CollisionBox()->checkRectangleCollision(squid.getHB()) && !immune)
		{
			gameOver = true;
		}
	}
}
/// <summary>
/// INCREASES DIFFICULTY BASED ON TIME PLAYED
/// </summary>
void Game::increaseEnemies()
{
	if (clock.getElapsedTime().asSeconds() > 55.f)
	{
		currentEnemies++;
		if (currentEnemies >= 6)
		{
			currentEnemies = 6;
		}
		clock.restart();
	}
}
/// <summary>
/// PLAYER TAKES DAMAGE, SETS DAMAGE STATE AND ANIMATES LOSS OF BUBBLES AND TUMBLE
/// </summary>
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
/// <summary>
/// ENABLES LEAP GESTURES
/// </summary>
void Game::enableGestures()
{
	controller.addListener(listener);

	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
	controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
}
/// <summary>
/// DETECTS LEAP GESTURES
/// </summary>
/// <param name="frame"> CURRENT LEAP FRAME</param>
/// <returns></returns>
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
/// <summary>
/// CHECKS WHAT ACTION HAND IS DOING AND WHICH HAND
/// </summary>
/// <param name="controller"></param>
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

/// <summary>
/// CHECKS WHICH HAND
/// </summary>
/// <param name="controller"></param>
/// <returns></returns>
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

/// <summary>
/// DELETES ALL ENTITIES AND RESPAWN ON GAME OVER
/// </summary>
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
	delete myChest;

	for (int i = 0; i < 4; i++)
	{
		delete kelp[i];
		delete seabush[i];
	}

}

/// <summary>
/// RESETS ALL BOOLS AND MAKES NEW GAME ENEMIES AND ENTITIES
/// </summary>
void Game::restartGame()
{
	myOverLay.reset();

	input.setCurrent(gpp::Events::Event::DAMAGE_TAKEN_STOP);

	clock.restart();
	currentEnemies = 1;
	tumble = 0;
	immuneTimer = 0;
	damaged = false;
	immune = false;
	bossFight = false;

	player = new Player(player_animated_sprite);

	bg1 = new Background(BG_, 2.4, 3, 3, 2000);
	bg2 = new Background(BG_ROCKS, 3, 2, 2, 1920);

	for (int i = 0; i < 4; i++)
	{
		kelp[i] = new Background(2, 2, rand() % 1920, WINDOW_HEIGHT - 50, KELP);
		seabush[i] = new Background(2, 2, rand() % 1920, WINDOW_HEIGHT - 50, SEABUSH);
	}

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

	myChest = new Chest();
	myChest->initialise();
	
	squid.reset();

	bgMusic.play();
}

/// <summary>
/// RESETS PLANT POSITION
/// </summary>
void Game::plantReset()
{
	if (myPlant->plantPos().x < -400)
	{
		myPlant->setPosition();
	}
	if (myChest->chestPos().x < -500)
	{
		myChest->setPosition();
	}
}
/// <summary>
/// BUBBLE COLLISION TO GAIN OXYGEN
/// </summary>
void Game::plantBubbleCollision()
{

	if (player->CollisionBox()->checkRectangleCollision(myPlant->CollisionBox()))
	{
		playBreathing();
		myPlant->bubbleSetPos();
		player->bubblesHit();

	}

}

/// <summary>
/// ALL SQUID FUNCTIONS
/// </summary>
void Game::squidControl()
{
	if (squid.getScale()>=2)
	{
		bossFight = true;
	}
	if (squid.returnDashes() == 2)
	{
		bossFight = false;
		squid.reset();
	}
	if (!bossFight)
	{
		squid.update(player->getPosition());
	}
	if (bossFight)
	{
		squid.bossEntrance(player->getPosition());
	}

}

void Game::playBG()
{
	if (!bgMusic.openFromFile("ASSETS\\AUDIO\\bgmusic.wav"))
	{
		std::cout << "error laoding music";
	}
	if (!ambience.openFromFile("ASSETS\\AUDIO\\ambience.wav"))
	{
		std::cout << "error loading ambiecne";
	}
	ambience.setLoop(true);
	ambience.setVolume(20);
	ambience.play();

	bgMusic.setLoop(true);
	bgMusic.setVolume(10);
	bgMusic.play();
}

void Game::playBreathing()
{
	if (!breathing.openFromFile("ASSETS\\AUDIO\\breath.wav"))
	{
		std::cout << "error loading ambiecne";
	}
	breathing.setVolume(20);
	breathing.play();
}





