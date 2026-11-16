// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

#include "MobileObject.h"

MobileObject::MobileObject(Game* game, Texture* myTexture, istream& juegoGuardado) : SceneObject(game, myTexture, juegoGuardado){

	char clave = juegoGuardado.get();
	string u_str;
	while (clave != ' ')
	{
		u_str + clave;
		clave = juegoGuardado.get();
	}
	string v_str;
	clave = juegoGuardado.get();
	while (clave != ' ')
	{
		v_str += clave;
		clave = juegoGuardado.get();
	}
	float u = stof(u_str);
	float v = stof(v_str);
	vel = { u, v };
};
bool MobileObject::update(float dt) {

	pos.move(vel * dt); // Se sobreescribe el método update para que se desplace el objeto en función de su velocidad.

	return true; // Devuelve si sigue existiendo el objeto.
}
void MobileObject::saveObj(ostream& archivo) {
	SceneObject::saveObj(archivo);
	archivo << " " << vel.getX() << " " << vel.getY();
}
