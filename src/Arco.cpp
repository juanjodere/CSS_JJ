#include "Arco.h"

// Llama al método de la textura que se encarga de dibujarla, en la posición de pos.
void
Arco::render() const{
	texture->renderFrame(pos.to_sdl(), 0, descargado);
}

// Mueve el rectángulo pos del arco en función de la velocidad, la dirección, y el tiempo desde el último movimiento.
bool
Arco::update(int dt) {
	move(VEL, dir, dt);

	return true;
}

// Comprueba si el arco debe moverse, o si está en los bordes de la pantalla.
// Si lo está, anula la dirección, y si no, realiza el movimiento.
void
Arco::move(Vector2D<float> vel, float dir, int dt) {
	if (pos.getTopLeftCorner().getY() < 0 && dir == -1)
		dir = 0;
	else if (pos.getTopLeftCorner().getY() + pos.getHeight() > game->WINDOW_HEIGHT && dir == 1)
		dir = 0;
	else
	pos.move(vel * dir * dt);
}

// Recibe el input del teclado y ratón.
// Se moverá hacia arriba si se presiona la flecha hacia arriba o W.
// Se moverá hacia abajo si se presiona la flecha hacia abajo o S.
// Recargará con click derecho, flecha hacia derecha o D.
// Disparará con click izquierdo, flecha hacia izquierda o A.
// Los cambios de movimiento se realizarán cambiando la dirección del movimiento, que procesará en move.
void
Arco::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		const bool* keys = SDL_GetKeyboardState(nullptr); // Analiza teclado.
		if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) { // si abajo o S.
			// Cambia dir de la velocidad
			dir = 1;
		}
		else if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) { // Si arriba o W.
			// Cambia dir de la velocidad
			dir = -1;
		}
		else if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) { // Si izq o A.
			// Dispara
			if (!descargado) {
				descargado = true;
				game->createArrow({ 2, 39 }, pos.getTopLeftCorner());
				numFlechas--;
			}
		}
		else if ( (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) && numFlechas > 0) { // Si quedan flechas, y der o D.
			// Recarga
			if (descargado) descargado = false;
		}
	}
	else dir = 0;
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && numFlechas > 0) { // Comprueba ratón y tiene flechas.
		float x, y;
		SDL_MouseButtonFlags flags = SDL_GetMouseState(&x, &y);
		if (flags & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) { // Click izquierdo.
			if (!descargado) {
				descargado = true; 
				game->createArrow({ 2, 39 }, pos.getTopLeftCorner());
				numFlechas--;
			}
		}
		if (flags & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)) { // Click derecho.
			if (descargado) descargado = false;
		}
	}
}

// Recibe un número de flechas iniciales, y lo guarda. Cuando numFlechas sea 0, no podrá disparar ni recargar.
void Arco::setNumArrows(int na) {
	numFlechas = na;
}
