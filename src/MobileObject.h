// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

// Esta subclase de SceneObject, se utilizará al tratar con objetos que se mueven por la escena independientemente de
// otros factores.

#pragma once
#include "vector2D.h"
#include "SceneObject.h"

class Game;

class MobileObject: public SceneObject
{
protected:

	Vector2D<float> vel; // El vector (velX, velY) que define la velocidad del objeto.

public:

	MobileObject(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, Vector2D<float> myVel, int anim = 0) :
		SceneObject(myGame, myTexture, myPos, myWidht, myHeight, anim),
		vel(myVel)
	{};


	MobileObject(Game* game, Texture* myTexture, istream &juegoGuardado);
	
	bool update(float dt) override; // Realiza un desplazamiento (cambiando pos) en función de la velocidad y el deltaTime.

	virtual void saveObj(ostream&);
};

