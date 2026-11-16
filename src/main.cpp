//
// Alterado por Camilo Snadoval Sánchez y Juan José de Reyna Godoy.
// 
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"

string lvl1 = "1.txt";
string lvl2 = "2.txt";

// Crea un objeto Game, carga un nivel, y maneja las excepciones que capture.
// Si captura una, muestra un mensaje al usuario, y espera a que responda para cerrar el programa.
int main(int argc, char* argv[])
{
	try {
		Game myGame = Game(); // Crea.
		myGame.LoadLevel(lvl1); // Lee un nivel.
		myGame.run(); // Empieza el juego.
	}
	catch (GameError error) {
		
		cout << error.what() << endl;

		cin; // Espera un input.

		return 1;
	}
	return 0;
}
