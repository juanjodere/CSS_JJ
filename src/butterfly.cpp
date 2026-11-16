#include "butterfly.h"
#include "game.h"
#include <random>

//Random Generator
//std::mt19937_64 randomGenerator;

butterfly::butterfly(Game* game, Texture* myTexture, istream& juegoGuardado) : MobileObject(game, myTexture, juegoGuardado) {

	char clave = juegoGuardado.get();
	string a;
	//cout << clave;
	while (clave != ' ')
	{
		//cout << clave;
		a += clave;
		clave = juegoGuardado.get();
	}
	SceneObject::animIndex = stoi(a);
};

bool butterfly::update(float dt) {

	if (dead) {

		return manageFalling(dt);

	}
	else {

		manageMovement(dt);

	}

	return true;

}

// privates

void butterfly::manageMovement(float dt) {

	if (actualTime >= DIRECTION_CHANGING_TIME) {

		/*int dirX = std::uniform_int_distribution<int>(0, 1)(randomGenerator); // Genera un aleatorio entre 0 y 1, y si sale 0, lo cambia por -1
		if (dirX == 0) dirX == -1;
		int dirY = std::uniform_int_distribution<int>(0, 1)(randomGenerator);// Genera un aleatorio entre 0 y 1, y si sale 0, lo cambia por -1
		if (dirY == 0) dirY == -1; */
		int dirX = -1; int dirY = 1;
		giveDirection(dirX, dirY);
		
		actualTime = 0;
	}
	else actualTime += dt;

	manageBorders();

	MobileObject::update(dt);

	manageAnimations();

}

void butterfly::manageBorders(){

	if (pos.getTopLeftCorner().getY() < 0 || pos.getTopLeftCorner().getY() + pos.getHeight() > _game->WINDOW_HEIGHT) {

		giveDirection(1, -1) ;

	}
	else if (pos.getTopLeftCorner().getX() < 0 || pos.getTopLeftCorner().getX() + pos.getWidth() < _game->WINDOW_WIDTH) {

		giveDirection(-1, 1);

	}

}

void butterfly::giveDirection(int dirX, int dirY) {

	vel = { vel.getX() * dirX, vel.getY() * dirY };

}

void butterfly::manageAnimations() {

	manageRows(); // Maneja la animación que se ejecutará.
	
	manageColumns(); // Maneja cuál frame se ejecuta de la animación que se esté haciendo.
	
}

void butterfly::manageRows() {

	int dirX = vel.getX();

	if (animIndex == 1 && dirX < 0) {
		animIndex == 2;
	}
	else if (animIndex == 0 && dirX > 0) {
		animIndex == 3;
	}
	else if (frameIndex == text->getNumColumns()) {

		if (animIndex == 2) animIndex == 0;
		else if (animIndex == 3) animIndex == 1;
	}

}

void butterfly::manageColumns() {
	if (frameIndex < text->getNumColumns()) { // Si no se ha acabado la animación.
		frameIndex++; // Cambia frame.
	}
	else frameIndex = 0; // Si se ha acabado, reinicia la animación.
}

bool butterfly::manageFalling(float dt) {

	Fall(dt);

	return manageDeleting();

}

void butterfly::Fall(float dt) {

	MobileObject::update(dt);

}

bool butterfly::manageDeleting() {

	if (pos.getTopLeftCorner().getY() + pos.getHeight() <= 0) return false;
	else return true;// Si sale de la pantalla.

}

bool butterfly::hit(const Rectangle& rect) {

	vel = {0, FALLING_VEL};

	dead = SceneObject::hit(rect);

	return dead;
}

void butterfly::saveObj(ostream& archivo) {
	archivo << "M";
	MobileObject::saveObj(archivo);
	archivo << " " << SceneObject::animIndex << "\n";
}
