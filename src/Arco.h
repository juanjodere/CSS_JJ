// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "game.h"

//Declaracioón anticipada
class Game;

class Arco
{
private:

	const float WIDTH = 90;
	const float HEIGHT = 90;
	// Velocidad de movimiento.
	Vector2D<float> VEL = {0, 0.5}; // pix / ms

	// Valdrá true (1) si está descargado, y false (0) si tiene flecha.
	bool descargado = true;

	Texture* texture;

	// Posicion y dimesiones.
	Rectangle pos;

	// Dirección del movimiento.
	float dir = 0;

	// Número de flechas que tendrá disponible el jugador.
	int numFlechas;

	// Puntero a game.
	Game* game;

	

public:

	Arco(Point2D<float> pos, Texture* textr, Game* game) :
		texture(textr),
		pos(pos, WIDTH, HEIGHT),
		numFlechas(0),
		game(game)
	{
	};

	void render() const;

	void move(Vector2D<float> vel, float dir, int dt);

	void handleEvent(const SDL_Event& event);

	bool update(int dt);
	
	void setNumArrows(int na);

};

