// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#include "flecha.h"
#include "game.h"

// Los punteros con memoria en el heap los iguala a null, sin borrarlos, ya que el game ya los 
// borrará en su destructor.
flecha::~flecha() {
	text = nullptr;
	_game = nullptr;
}

// Se mueve, y comprueba si ha habido colisión con algún globo.
// Si ha salido de la ventana, devuelve false para que el Game lo destruya.
bool flecha::update(float dt) {
	//cout << "pasando";
	MobileObject::update(dt);
	float tip_width = pos.getWidth() / 4; // Colisión de la punta de la flecha.
	_game->checkCollison(Rectangle({tip_width * 3 + pos.getTopLeftCorner().getX(), pos.getTopLeftCorner().getY()}, tip_width, pos.getHeight())); // Envia rectángulo de la punta de flecha a ver si colisiona.
	if (pos.getTopLeftCorner().getX() > _game->WINDOW_WIDTH) return false; // Si se sale de la
	else if (pos.getTopLeftCorner().getX() < -pos.getWidth()) return false; // pantalla se elimina.
	return true;

}
void flecha::saveObj(ostream& archivo) {
	archivo << "A";
	MobileObject::saveObj(archivo);
	archivo << "\n";
}
