// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "texture.h"
#include "SceneObject.h"

//Declaracioón anticipada
//class Game;

class Arco : public SceneObject {
private:
	// La velocidad a la que se moverá el arco.
	Vector2D<float> vel;

	// Valdrá true (1) si está descargado, y false (0) si tiene flecha.
	bool descargado = true;

	// Dirección del movimiento.
	float dir = 0;

	// Número de flechas que tendrá disponible el jugador.
	int numFlechas = 0;

public:

	Arco(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, Vector2D<float> myVel) :
		SceneObject(myGame, myTexture, myPos, myWidht, myHeight),
		vel(myVel)
	{};

	void move(Vector2D<float> vel, float dir, int dt); // Realiza el movimiento del objeto cambiando la posición del rect pos en función de la velocidad, dirección y deltaTime.

	void handleEvent(const SDL_Event& event); // Maneja el input del jugador y cambia su estado (dir) en función de él.

	bool update(float dt) override; // Cambia el estado (pos) en función de la dirección de movimiento (dir).
	
	void setNumArrows(int na); // Cambia el número de flechas disponibles. Se llama al cargar un nivel desde un archivo.

};
