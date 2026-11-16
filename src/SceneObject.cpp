// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

// Esta subclase de GameObject se usará para objetos que estén presentes en la escena, es decir, una posición
// y dimensiones.

#include "SceneObject.h"


SceneObject::SceneObject(Game* game, Texture* myTexture, istream& juego): GameObject(game), text(myTexture) {
	
	char clave = juego.get();
	clave = juego.get();
	string x_str;
	while (clave != ' ')
	{
		x_str += clave;
		clave = juego.get();
	}
	string y_str;
	clave = juego.get();
	while (clave != ' ')
	{
		y_str += clave;
		clave = juego.get();
	}
	string w;
	clave = juego.get();
	while (clave != ' ')
	{
		w += clave;
		clave = juego.get();
	}
	string h;
	clave = juego.get();
	while (clave != ' ')
	{
		h += clave;
		clave = juego.get();
	}
	width = stof(w);
	height = stof(h);
	float x = stof(x_str);
	float y = stof(y_str);
	pos = Rectangle({x,y}, width, height);
}

void SceneObject::render() const {
	text->renderFrame(pos.to_sdl(), animIndex, frameIndex);
}

bool SceneObject::hit(const Rectangle& collisioner) {
	return pos.hasIntersection(collisioner);
}
void SceneObject::saveObj(ostream& archivo) {
	archivo << " " << pos.getTopLeftCorner().getX() << " " << pos.getTopLeftCorner().getY();
	archivo << " " << width << " " << height;
}
