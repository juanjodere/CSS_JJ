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
	catch (string error) {
		// TODO: manejar excepciones
		if (error == "ERROR: Fichero de imagen no encontrado o inválido.") {
			cout << "Alguna textura no se ha encontrado. Pulse enter para terminar el programa.";
		}
		else if (error == "ERROR: No se ha encontrado el fichero del nivel.") {
			cout << "El fichero del nivel no se ha encontrado en la carpeta levels. Pulse enter para terminar el programa.";
		}
		else if (error == "ERROR: No se han podido crear la ventana y el renderer." || error == "ERROR: No se ha podido inicializar SDL.") {
			cout << "Ha habido un error de SDL. Pulse enter para terminar el programa.";
		}
		else {
			cout << "El programa ha tenido un error inesperado. Pulse enter para terminar el programa.";
		}

		cin; // Espera un input.

		return 1;
	}
	return 0;
}
