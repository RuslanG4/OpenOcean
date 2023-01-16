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
#include<Leap.h>

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
	
	//Player TEXTURES AND SPRITE
	sf::Texture player_texture;
	Player* player;
	AnimatedSprite player_animated_sprite;

	sf::Sprite m_bubbles;
	sf::Texture m_bubblesTexture;
	int bubbleTimer = 0;
	int bubbleFrame = 0;
	void animateBubbles();

	bool gameOver = false;

	OverLay myOverLay;
	GameOver gameOverScreen;

	//PLAYER ANIMATION EVENTS
	gpp::Events input;
	void FSM();
	//BACKGROUND
	Background* bg1;
	Background* bg2;
	//ENEMIES
	Enemy* fish[5];
	Enemy* bigFish[5];
	Enemy* longFish[5];
	Enemy* mine[5];
	//ENTITES
	Plant* myPlant;
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

	Leap::Controller controller;
	Leap::Listener listener;
	void enableGestures();
	int detectGestures(Leap::Frame frame);
	void checkHand(Leap::Controller controller);
	std::string handCheck(Leap::Controller controller);

	void deleteEntities();
	void restartGame();

	void pearlReset();
	void pearlCollision();


};

#endif // !GAME_HPP

