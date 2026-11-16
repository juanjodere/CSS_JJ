// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"

// Tiempo que pasa entre un frame y otro en la animación de destruir.
constexpr float CICLES_BETWEEN_FRAMES = 150;

class Game;

class Balloon : public MobileObject
{
private:
	// Detecta el estado del globo.
	bool explotado = false;

	// Guarda el tiempo actual de la animación de destrucción.
	float ciclAnimAct = CICLES_BETWEEN_FRAMES;

public:

	Balloon(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, Vector2D<float> myVel, int myColor) :
		MobileObject(myGame, myTexture, myPos, myWidht, myHeight, myVel, myColor)
	{};

	Balloon(Game* game, Texture* myTexture, istream& juegoGuardado);

	bool hit(const Rectangle&) override; // Cambia el estado de explotado en función de si colisiona con el rectángulo pasado o no.

	bool update(float dt) override; // Actualiza el estado del globo, en función de si está explotado o no.

	bool popBalloon(); // Cambia los frames del globo. Se usa en el update.

	void saveObj(ostream& archivo); // Cambia los frames del globo. Se usa en el update.
};

