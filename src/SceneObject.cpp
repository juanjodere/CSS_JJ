// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

// Esta subclase de GameObject se usará para objetos que estén presentes en la escena, es decir, una posición
// y dimensiones.

#include "SceneObject.h"


SceneObject::SceneObject(Game* game, Texture* myTexture, istream& juego): GameObject(game), text(myTexture) {
	
	char clave = juego.get();
	clave = juego.get();
	string x_str;
	//cout << " bsc x ";
	while (clave != ' ')
	{
		x_str += clave;
		cout << clave;
		clave = juego.get();
	}
	string y_str;
	clave = juego.get();
	//cout << " busc y ";
	while (clave != ' ')
	{
		y_str += clave;
		//cout << clave;
		clave = juego.get();
	}
	string w;
	clave = juego.get();
	//cout << clave;
	while (clave != ' ')
	{
		w += clave;
		clave = juego.get();
		//cout << clave;
	}
	string h;
	clave = juego.get();
	//cout << clave;
	while (clave != ' ')
	{
		h += clave;
		clave = juego.get();
		//cout << clave;
	}
	//cout << " valores ";
	//cout << w;
	//cout << h;
	//cout << x_str;
	//cout << y_str;
	width = stof(w);
	//cout << " extw ";
	height = stof(h);
	//cout << " exth ";
	float x = stof(x_str);
	//cout << " extx ";
	float y = stof(y_str);
	//cout << " exty ";
	pos = Rectangle({x,y}, width, height);
}

void SceneObject::render() const {
	text->renderFrame(pos.to_sdl(), animIndex, frameIndex);
}

bool SceneObject::hit(const Rectangle& collisioner) {
	return pos.hasIntersection(collisioner);
}
void SceneObject::saveObj(ostream& archivo) {
	archivo << " " << floor(pos.getTopLeftCorner().getX()) << " " << floor(pos.getTopLeftCorner().getY());
	archivo << " " << width << " " << height << " ";
}
