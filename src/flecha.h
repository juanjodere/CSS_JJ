// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "game.h"

//Declaracioón anticipada
class Game;


class flecha
{
private:

	 float WIDTH = 90;
	 float HEIGHT = 20;

	Texture* texture;

	// Posicion y dimesiones.
	Rectangle pos;

	// Velocidad de movimiento.
	Vector2D<float> vel;

	// Puntero a game.
	Game* game;


public:

	flecha(Point2D<float> pos, Texture* textr, Game* game) :
		texture(textr),
		pos(pos, WIDTH, HEIGHT),
		game(game),
		vel ({1, 0})
	{
	};

	~flecha();

	bool hit(const Rectangle& obj);

	void render() const;

	void move(int dt);

	bool update(int dt);



};

