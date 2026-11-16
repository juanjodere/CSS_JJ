#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"


constexpr float DIRECTION_CHANGING_TIME = 500;

constexpr float FALLING_VEL = 0.45;

class Game;

class butterfly : public MobileObject
{
private:

	float actualTime = 0;

	bool dead = false; // Guarda si ha sido golpeada por la flecha.

	void giveDirection(int dirX, int dirY);
	
	void manageMovement(float dt);

	bool manageFalling(float dt);

	void Fall(float dt);

	bool manageDeleting();

	void manageBorders();

	void manageAnimations();

	void manageColumns();

	void manageRows();

public:

	butterfly(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, Vector2D<float> myVel, int anim = 0) :
		MobileObject(myGame, myTexture, myPos, myWidht, myHeight, myVel, anim)
	{};

	butterfly(Game * game, Texture * myTexture, istream & juegoGuardado);

	bool update(float dt) override;

	bool hit(const Rectangle&) override;

	void saveObj(ostream& archivo); // Cambia los frames del globo. Se usa en el update.

};

