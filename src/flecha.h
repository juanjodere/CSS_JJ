// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "texture.h"
#include "MobileObject.h"

//Declaracioón anticipada
class Game;


class flecha : public MobileObject
{
public:

	flecha(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, Vector2D<float> myVel) :
		MobileObject(myGame, myTexture, myPos, myWidht, myHeight, myVel)
	{};

	flecha(Game * game, Texture * myTexture, istream & juegoGuardado);

	~flecha();

	bool update(float dt) override; // Actualiza el estado de la flecha (pos) y devuelve false si se tiene que eliminar.

	void saveObj(ostream& archivo);
};

