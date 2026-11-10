// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

// Esta subclase de GameObject se usará para objetos que estén presentes en la escena, es decir, una posición
// y dimensiones.

#include "SceneObject.h"

void SceneObject::render() const{
	text->renderFrame(pos.to_sdl(), animIndex, frameIndex);
}

bool SceneObject::hit(const Rectangle& collisioner) {
	return pos.hasIntersection(collisioner);
}
