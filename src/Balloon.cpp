#include "Balloon.h"


const int textureSize = 256;

Balloon::Balloon(Game* game, Texture* myTexture, istream& juegoGuardado) : MobileObject(game, myTexture, juegoGuardado){

	char clave = juegoGuardado.get();
	string c;
	while (clave != ' ')
	{
		c += clave;
		clave = juegoGuardado.get();
	}
	string e;
	clave = juegoGuardado.get();
	while (clave != ' ' && clave != '\n')
	{
		e += clave;
		clave = juegoGuardado.get();
	}
	SceneObject::animIndex = stoi(c);
	if (stoi(e)>0) explotado = true;

};

// Cambia el frame de la animación de explosión del globo a la siguiente, y devuelve true cuando esta termina.
bool
Balloon::popBalloon() {
	if (frameIndex < textureSize / width) { // Si no se ha acabado la animación.
		frameIndex++; // Cambia frame.
	}
	else return true; // Destruyelo.
	return false; // No lo destruyas aún.
}

// Mueve el globo si no se ha explotado, y si sigue en la pantalla.
// Si no sigue en la pantalla, devuelve false para que el Game lo destruya.
// Si se ha explotado y han pasado los ciclos adecuados, llama a popBallon, reinicia el temporizador para esperar entre frame y frame.
// Si está destruido, pero aún no han pasado los ciclos adecuados, suma uno al contador de ciclos.
bool 
Balloon::update(float dt) {
	bool borra = false;
	if (explotado) { // Si le ha dado la flecha.
		if (ciclAnimAct >= CICLES_BETWEEN_FRAMES) { // Si han pasado los ciclos adecuados
			borra = popBalloon(); // Cambia frame.
			ciclAnimAct = 0; // Reinicia temp.
		}
		else ciclAnimAct += dt;
		return !borra;
	}
	else {
		if (pos.getTopLeftCorner().getY() + pos.getHeight() <= 0) return false; // Si sale de la pantalla.
		MobileObject::update(dt);
	}
}

// Devuelve true si ha colisionado con tip (punta de la flecha).
bool Balloon::hit(const Rectangle& tip) {
	if (!explotado)
		explotado = MobileObject::hit(tip); // explotado es true si tip interseca con pos.
	return explotado;
}

void Balloon::saveObj(ostream& archivo) {
	archivo << "B";
	MobileObject::saveObj(archivo);
	archivo << " " << SceneObject::animIndex << " " << explotado << "\n";
}
