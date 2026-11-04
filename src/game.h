// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include "vector2D.h"
#include "rectangle.h"
#include "Balloon.h"
#include "Arco.h"
#include "flecha.h"

using namespace std;

// Declaraciones anticipadas
class Texture;
class flecha;
class Arco;


class Game
{
public:
	// Número de actualizaciones por segundo
	static constexpr int FRAME_RATE = 30; // act / s
	// Periodo entre actualizaciones en milisegundos
	static constexpr int FRAME_PERIOD = 1000 / FRAME_RATE; // ms / act
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;

	enum TextureName
	{
		BOW = 0,
		BALLOON, 
		ARROW,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update(int dt);
	void handleEvents();
	void createBalloon(Point2D<float> origin);

	bool exit;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego
	vector<Balloon*> balloons;
	vector<flecha*> arrows;
	Arco* Jugador;
	int baldelay;

public:
	Game();
	~Game();

	//
	void LoadLevel(const string& entrada);

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	// bool checkCollision(const Rectangle& rect);
	void createArrow(Point2D<float> reltvOrigin, Point2D<float> bowPos);


	// Comprueba si el rectángulo recibido, que es el de la punta de la flecha, colisiona con algún globo.
	// Devuelve true si es el caso.
	bool checkCollison(const Rectangle&);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
