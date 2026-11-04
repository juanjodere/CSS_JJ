#include "Balloon.h"

const int textureSize = 256;

// Llama a la función que hace que la textura se dibuje en la posición del rectángulo pos.
void
Balloon::render() const{
	textura->renderFrame(pos.to_sdl(), colorIndex, indice);
}

// Mueve el rectángulo pos en función de la velocidad y el tiempo que ha pasado desde el último movimiento (dt).
void
Balloon::move(int dt) {
	pos.move(vel * dt);
}

// Cambia el frame de la animación de explosión del globo a la siguiente, y devuelve true cuando esta termina.
bool
Balloon::popBalloon() {
	if (indice < textureSize / WIDTH) { // Si no se ha acabado la animación.
		indice++; // Cambia frame.
	}
	else return true; // Desttruyelo.
	return false; // No lo destruyas aún.
}

// Mueve el globo si no se ha explotado, y si sigue en la pantalla.
// Si no sigue en la pantalla, devuelve false para que el Game lo destruya.
// Si se ha explotado y han pasado los ciclos adecuados, llama a popBallon, reinicia el temporizador para esperar entre frame y frame.
// Si está destruido, pero aún no han pasado los ciclos adecuados, suma uno al contador de ciclos.
bool 
Balloon::update(int dt) {
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
		move(dt); // Lo mueve.
	}
	return true;
}

// Devuelve true si ha colisionado con tip (punta de la flecha).
bool Balloon::hit(const Rectangle& tip) {
	if (!explotado)
		explotado = pos.hasIntersection(tip); // explotado es true si tip interseca con pos.
	return explotado;
}
