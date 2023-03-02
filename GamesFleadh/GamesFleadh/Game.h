/// <summary>
/// Ruslan Gavrilov
/// December 2022
///
/// 
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"Player.h"
#include"Events.h"
#include"AnimatedSprite.h"
#include"Background.h"
#include"Enemy.h"
#include"Collision.h"
#include"Fish.h"
#include"BigFish.h"
#include"LongFish.h"
#include"Mine.h"
#include"OverLay.h"
#include"GameOver.h"
#include"Plant.h"
#include"Chest.h"
#include"Squid.h"
#include"SplashScreen.h"
#include"Shell.h"
#include<Leap.h>

enum class gameState
{
	SPLASH,
	GAMEPLAY
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void processKeyRelease(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setupFontAndText();

	bool m_exitGame; // control exiting game

	sf::RenderWindow m_window; // main SFML window

	sf::Font m_ArialBlackfont; // font used by message

	//splashScreen
	SplashScreen splash;
	sf::Clock splashClock;
	gameState state = gameState::SPLASH;
	void updateSplashClock();

	
	//Player TEXTURES AND SPRITE
	sf::Texture player_texture;
	Player* player;
	AnimatedSprite player_animated_sprite;

	//PLAYER BUBBLES
	sf::Sprite m_bubbles;
	sf::Texture m_bubblesTexture;
	int bubbleTimer = 0;
	int bubbleFrame = 0;
	void animateBubbles();

	//GAME EVENTS
	bool gameOver = false;
	bool bossFight = false;

	//SCREENS
	OverLay myOverLay;
	GameOver gameOverScreen;

	sf::RectangleShape darkness;

	//PLAYER ANIMATION EVENTS
	gpp::Events input;
	//BACKGROUND
	Background* bg1;
	Background* bg2;

	//BACKGROUNDPLANTS
	Background* kelp[4];
	Background* seabush[4];

	//ENEMIES
	Enemy* fish[6];
	Enemy* bigFish[6];
	Enemy* longFish[6];
	Enemy* mine[6];
	//SQUID
	Squid squid;

	//SHELLS
	Shell* shell[3];


	//ENTITES
	Plant* myPlant;
	Chest* myChest;
	//TAKING DAMAGE
	int tumble = 0;
	int immuneTimer = 0;
	bool damaged = false;
	bool immune = false;
	void damage();

	//COLLISION
	void fishColl();
	void increaseEnemies();
	int currentEnemies = 1;
	sf::Clock clock;

	//LEAP
	Leap::Controller controller;
	Leap::Listener listener;
	void enableGestures();
	int detectGestures(Leap::Frame frame);
	void checkHand(Leap::Controller controller);
	std::string handCheck(Leap::Controller controller);

	//RESTARTING GAME
	void deleteEntities();
	void restartGame();

	//PLANT
	void plantReset();
	void plantBubbleCollision();

	//SQUID CONTROLS
	void squidControl();


	//audio
	sf::Music bgMusic;
	sf::Music ambience;
	void playBG();
	sf::Music breathing;
	void playBreathing();

	


};

#endif // !GAME_HPP

