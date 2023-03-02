#include "Squid.h"

/// <summary>
/// UPDATES BLACKED OUT SQUID, SHADOW
/// </summary>
/// <param name="t_playerPos"></param>
void Squid::update(sf::Vector2f t_playerPos)
{
	animate();
	Scale();
	move();
}
/// <summary>
/// LOADS ALL TEXTURES AND INITILISES POSITIONS ETC
/// </summary>
void Squid::loadTextures()
{
	if (!squidT.loadFromFile("ASSETS\\IMAGES\\ColossalSquid.png"))
	{
		std::cout << "error";
	}
	//BOSS SQUID
	squid.setTexture(squidT);
	squid.setOrigin(155, 96);
	squid.setScale(scale, scale);
	squid.setPosition(position);
	squid.setTextureRect(sf::IntRect(0, 0, 310, 192));
	squid.setColor(sf::Color((139, 69, 19)));
	velocity.x = rand() % 3 + 1;
	squid.setRotation(90);
	//SQUID SHADOW
	squidBlackedOut.setTexture(squidT);
	squidBlackedOut.setOrigin(155, 96);
	squidBlackedOut.setScale(scale, scale);
	squidBlackedOut.setPosition(position);
	squidBlackedOut.setTextureRect(sf::IntRect(0, 0, 310, 192));
	squidBlackedOut.setColor(sf::Color((255, 255, 255, 128)));
	squidBlackedOut.setRotation(90);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
	m_box.setSize(sf::Vector2f(135, 250));

	hb = new Rectangle(squid.getPosition().x - 90, squid.getPosition().y - 170, 135, 200);

	light = Light{ sf::Vector2f(500,300) };
	light.scale(1, 1);
	light.setMaxLight(255);
	light.setIntensity(0.5);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));
}
/// <summary>
/// DRAWS BIG SQUID
/// </summary>
/// <param name="t_window"></param>
void Squid::render(sf::RenderWindow& t_window)
{
	t_window.draw(light.draw());
	t_window.draw(squid);
	//t_window.draw(m_box);
}

/// <summary>
/// ANIMATES BOTH SPRITES
/// </summary>
void Squid::animate()
{
	squidTimer++;
	if (squidTimer > 4)
	{
		squidFrame++;
		if (squidFrame > 11) //frame 44 is the last frame the robot is running
		{
			squidFrame = 0; //37 is the first frame the robot is running
		}
		squidTimer = 0;
	}
	int col = 0; 
	int row = squidFrame % 11; 

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 192;
	rectSourceSprite.width = 310;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	squid.setTextureRect(rectSourceSprite);
	squidBlackedOut.setTextureRect(rectSourceSprite);


}

/// <summary>
/// MOVES SQUID SHADOW
/// </summary>
void Squid::move()
{
	sf::Vector2f move{ 0,0 };
	if (squidBlackedOut.getPosition().x < -200)
	{
		velocity.x = -velocity.x; //GOES BACK AND FORTH
		BlackedOutposition.y = rand() % 600 + 100; //RANDOM Y POS
		squidBlackedOut.setRotation(90); //ROTATE WHICH WAY TO FACE
		scale += 0.35; //ADDS ONTO THE SCALE

	}
	if (squidBlackedOut.getPosition().x > WINDOW_WIDTH + 200)
	{
		velocity.x = -velocity.x;
		BlackedOutposition.y = rand() % 600 + 100;
		squidBlackedOut.setRotation(270);
		scale += 0.35;
	}
	move.x += velocity.x;
	BlackedOutposition += move;
	squidBlackedOut.setPosition(BlackedOutposition); //SETS POS

	light.followCentre(squidBlackedOut.getPosition());
	light.scale(scale,scale);
}

void Squid::Scale()
{
	if (scale > 2)
	{
		scale = 2; //SCALE MAX 2 , STARTS BOSS ENCOUNTER
	}
	squidBlackedOut.setScale(scale, scale);
}
/// <summary>
/// ENTERANCE OF BOSS
/// </summary>
/// <param name="playerPos"></param>
void Squid::bossEntrance(sf::Vector2f playerPos)
{
	light.followCentre(squid.getPosition());
	light.scale(scale, scale);
	light.setMaxLight(255);
	light.setIntensity(1);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));
	animate();
	if (!enterance)//DOES ENTERANCE
	{
		if (!start) //SETS POSITIONS ETC
		{
			position = { WINDOW_WIDTH-150,-400 };
			squid.setColor(sf::Color::White);
			squid.setScale(2, 2);
			squid.setPosition(position);
			squid.setRotation(180);
			start = true; //DONE SETTING

			m_box.setSize(sf::Vector2f(135, 250));
			m_box.setPosition(squid.getPosition().x - 90, squid.getPosition().y - 170);
		}
		if (squid.getPosition().y < 450)
		{
			squid.move(0, 3);
		}
		else//AS SOON AS SQUID REACHES <450 Y ENTERANCE IS OVER
		{
			squid.setRotation(0);
			m_box.setRotation(0);
			enterance = true;
		}
	}
	else //STARTS BOSS AI
	{
		aiMove(playerPos);
		dash();
	}
}

/// <summary>
/// BOSS MOVEMENT DECISIONS
/// </summary>
/// <param name="playerPos">PLAYER POS TO FOLLOW</param>
void Squid::aiMove(sf::Vector2f playerPos)
{
	light.followCentre(squid.getPosition());
	light.scale(scale, scale);
	light.setMaxLight(255);
	light.setIntensity(1);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));

	hb = new Rectangle(squid.getPosition().x - 90, squid.getPosition().y - 170, 135, 200);
	m_box.setPosition(squid.getPosition().x - 90, squid.getPosition().y-170);

	if (!isMoving)
	{ 
		//MOVES SQUID TO FOLLOW PLAYER
	chaseDirection = playerPos - squid.getPosition();
	thor::setLength(chaseDirection, float(1.5));
	position = squid.getPosition();
	position += chaseDirection;
	squid.setPosition(position);
	if (squid.getPosition().x < 1350) //MAKE SURE SQUID DOESNT GO PAST 1450
	{
		squid.setPosition(1350, squid.getPosition().y);
	}

	// TIMER FOR DECISIONS
	aiTimer++;
	if (aiTimer >= 30)
	{
		aiChoice = std::rand() % 10 + 1;
		aiTimer = 0;
	}
	if (aiChoice  == 3) // IF CHOICE IS 3 DASH IS ENABLES
	{
		isMoving = true;
	}
}
}

/// <summary>
/// DASH ATTACK FOR BIG SQUID, FOLLOWS PLAYER THEN SPINS AND DASHES
/// </summary>
void Squid::dash()
{
	if (isMoving)
	{
		spinTimer--;
		//squid.rotate(-1); //SPINS SQUID TO INDICATE DASH
		if (spinTimer <= 0) //AS SOON AS SPIN IS DONE, MOVES SQUID IN FAST DASH
		{
			//squid.setRotation(270);
			squid.move(-10, 0);
			m_box.setSize(sf::Vector2f(250, 130));
			m_box.setPosition(squid.getPosition().x - 150, squid.getPosition().y - 40);
			hb = new Rectangle(squid.getPosition().x - 150, squid.getPosition().y - 40, 250, 135);
			if (squid.getPosition().x < -200) //RESETS ENTIRE SQUID ENCOUNTER
			{
				enterance = false;
				start = false;
				isMoving = false;
				aiChoice = 0;
				spinTimer = 90;
				dashAmount++; //CAN DASH ONE MORE TIME AFTER FORST DASH
			}
		}
	}
}

/// <summary>
/// RESETS BIG SQUID VARIABLES AND SCALE
/// </summary>
void Squid::reset()
{
	light.setMaxLight(255);
	light.setIntensity(0.5);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));
	delete hb;
	aiTimer = 0;
	aiChoice = 0;
	spinTimer = 90;
	dashAmount = 0;
	scale = 0.5;
}



