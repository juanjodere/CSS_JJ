// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

#include "MobileObject.h"

bool MobileObject::update(float dt) {

	pos.move(vel * dt); // Se sobreescribe el método update para que se desplace el objeto en función de su velocidad.

	return true; // Devuelve si sigue existiendo el objeto.
}
