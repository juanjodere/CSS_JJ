// Juan José de Reyna Godoy y Camilo Sandoval Sánchez.

// Esta clase es un objeto del juego. Será una clase abstracta con métodos para actualizar su estado cada ciclo
// (update), y otra para dibujarse en pantalla (render).

#pragma once
class Game;

class GameObject
{
protected:

	Game* _game; // Puntero al Game

	GameObject(Game* myGame) :
		_game(myGame)
	{};
	
public:

	 ~GameObject() {
		_game = nullptr;
	};

	virtual bool update(float dt) = 0; // Actualiza el estado del objeto en función de su lógica.

	virtual void render() const = 0; // Se encarga de redibujar el objeto en función de sus atributos actualizados con update.
};

