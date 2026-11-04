// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#include "flecha.h"

// Los punteros con memoria en el heap los iguala a null, sin borrarlos, ya que el game ya los 
// borrará en su destructor.
flecha::~flecha() {
	texture == nullptr;
	game == nullptr;
}

// Muestra la textura en función de la posición.
void
flecha::render() const{
	texture->renderFrame(pos.to_sdl(),0, 0);
}

// Se mueve, y comprueba si ha habido colisión con algún globo.
// Si ha salido de la ventana, devuelve false para que el Game lo destruya.
bool
flecha::update(int dt) {
	move(dt);
	float tip_width = pos.getWidth() / 4;
	game->checkCollison(Rectangle({tip_width * 3 + pos.getTopLeftCorner().getX(), pos.getTopLeftCorner().getY()}, tip_width, pos.getHeight())); // Envia rectángulo de la punta de flecha a ver si colisiona.
	if (pos.getTopLeftCorner().getX() > game->WINDOW_WIDTH) return false;
	else if (pos.getTopLeftCorner().getX() < -pos.getWidth()) return false;
	return true;
}

// Mueve el rectángulo en función de su velocidad y el tiempo que ha pasado desde el último movimiento.
void
flecha::move(int dt) {
	pos.move(vel * dt);
}
