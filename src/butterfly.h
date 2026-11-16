#pragma once
#include "MobileObject.h"

//class Game;

class butterfly : public MobileObject
{
private:

	const float DIRECTION_CHANGING_TIME = 500;

	const float FALLING_VEL = 0.45;

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

	bool update(float dt) override;

	bool hit(const Rectangle&) override;
	butterfly(Game* game, Texture* myTexture, istream& juegoGuardado);
	void saveObj(ostream& archivo); // Cambia los frames del globo. Se usa en el update.

};

