// Alterado por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>


#include "texture.h"
#include "Balloon.h"

using namespace std;

// Constantes 
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/"; 

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	{"balloons.png", 7, 6},
	{"arrow.png",1,1},
};

// Guardan unidades de tiempo:
uint64_t startTime; // Momento en el que se inicia un ciclo.
uint64_t frameTime; // Tiempo que dura un frame.

//Random Generator
mt19937_64 randomGenerator;

// Variables de tipo punto, que guardan lugares base en los que instanciar globos y flechas
Point2D<float>  originBalloon(400, 600);
Point2D<float>  relativeOriginArrow(0, 4);

// Almacena los milisegundos que pasan entre la aparición de un globo y el siguiente.
int ballTimeCount = 0;

// Cambia variables del game y otros elementos en base a un archivo en la carpeta LEVEL_ROOT.
// Relanza excepciones en caso de capturar alguna.
void Game::LoadLevel(const string& entrada) {
	ifstream guardado;
	guardado.open(LEVEL_ROOT + entrada); // Abre el archivo.

	if (!guardado.is_open())throw string("ERROR: No se ha encontrado el fichero del nivel."); // Excepción
	else {
		string clave = " ";
		while (!guardado.fail()) { // Mientras siga abierto.
			guardado >> clave;
			if (clave[0] == '#') guardado.ignore('\n'); // Si es un comentario, ignora la línea.
			else if (clave == "baldelay") guardado >> baldelay; // lee baldelay.
			else if (clave == "arrows") { // lee número de flechas.
				int na = 0;
				guardado >> na;
				Jugador->setNumArrows(na);
			}
			else guardado.ignore('\n'); // Si no se sabe qué pone, se ignora la línea entera.
		}
	}

	guardado.close(); // Cierra el archivo.
}

// Construye el objeto Game e instancia un jugador.
// Relanza excepciones si captura alguna.
Game::Game()
  : exit(false), balloons(), baldelay(12)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw string("ERROR: No se ha podido inicializar SDL."); // Excepción

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
	throw string("ERROR: No se han podido crear la ventana y el renderer."); // Excepción

	// Carga las texturas.
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols); // Guarda las texturas en el array textures.
		}
	}
	catch (...) {
		// Libera la memoria que se haya reservado.
		for (size_t i = 0; i < textures.size(); i++) {
			delete textures[i];
			textures[i] = nullptr;
		}

		throw string("ERROR: Fichero de imagen no encontrado o inválido."); // Excepción
	}
	// Crear los objetos del juego
	Jugador = new Arco({0,250}, getTexture(BOW), this);
}

// Se libera la posible memoria reservada.
Game::~Game()
{
	delete Jugador; // Borra el jugador que está en el heap
	Jugador = nullptr;

	for (size_t i = 0; i < textures.size(); i++) { // Borra las texturas del heap.
		delete textures[i];
		textures[i] = nullptr;
	}

	for (size_t i = 0; i < arrows.size(); ++i) { // Borra las flechas que existiesen.
		delete arrows[i];
		arrows[i] = nullptr;
	}

	for (size_t i = 0; i < balloons.size(); ++i) { // Borra los globos que existiesen.
		delete balloons[i];
		balloons[i] = nullptr;
	}

	// Deja que el resto de variables salgan de término.
}

// Renderiza La pantalla, llamando a los renderizadores de cada elemento.
void
Game::render() const
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 190, 80, 0);

	Jugador->render(); // Renderiza el jugador.

	for (int i = 0; i < balloons.size(); ++i) { // Renderiza globos.
		balloons[i]->render();
	}
	for (int i = 0; i < arrows.size(); ++i) { // Renderiza flechas.
		arrows[i]->render();
	}

	SDL_RenderPresent(renderer);
}

// Procesa los cambios de cada elemento.
void
Game::update(int dt)
{
	Jugador->update(dt); // El jugador realiza sus cambios de estado.

	for (int i = 0; i < balloons.size(); ++i) { // Los globos realizan sus cambios de estado.
		bool active = balloons[i]->update(dt);
		if (!active) { // Si debe borrar un globo, lo borra.
			delete balloons[i];
			balloons.erase(balloons.begin() + i);
		}
	}

	for (int i = 0; i < arrows.size(); ++i) { // Las flechas realizan cambios de estado.
		bool active = arrows[i]->update(dt);
		if (!active) { // Si debe borrar una flecha, la borra.
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
		}
	}

	ballTimeCount += dt; // Actualiza el tiempo para que se cree otro globo.
	if (ballTimeCount >= baldelay) {
		createBalloon(originBalloon);  // Si el tiempo ha pasado, crea un globo, y reinicia el tiempo.
		ballTimeCount = 0;
	}

}

// Lleva el bucle principal del programa, llamando a handle events, update y render.
// fuerza que se ejecute un bucle cada FRAME_PERIOD tiempo.
void
Game::run()
{
	while (!exit) {
		startTime = SDL_GetTicks(); // Momento en el que inicia

		handleEvents();
		update(FRAME_PERIOD);
		render();
		frameTime = SDL_GetTicks() - startTime; // Actualiza el tiempo actual.
		if (frameTime < FRAME_PERIOD) // Fuerza que el bucle empiece cada FRAME_PERIOD
			SDL_Delay(FRAME_PERIOD - frameTime);
	}
}

// Maneja el input del jugador, llamando los métodos handleevents de los objetos que lo necesiten.
void
Game::handleEvents()
{
	SDL_Event event;

	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) // Si se pulsa la tecla de salir del juego, acaba el bucle.
			exit = true;

		Jugador->handleEvent(event);// El arco maneja sus eventos
	}
}

// Crea un globo, con coordenada en x, color y velocidad aleatoria.
void
Game::createBalloon(Point2D<float> origin)
{	// Aleatoriza el color (fila de la textura), velocidad y posición del globo.
	int color = uniform_int_distribution<int>(0, 6)(randomGenerator);
	float speedVar = uniform_real_distribution<float>(0.05, 0.5)(randomGenerator);
	float posVar = uniform_real_distribution<float>(-100, 325)(randomGenerator);
	Point2D<float> pos = { origin.getX() + posVar, origin.getY()};

	balloons.push_back(new Balloon(pos, { 0, -speedVar }, color, getTexture(BALLOON), 0)); // Lo crea y mete al vector.
}

// Crea una flecha y la mete al vector de flechas.
void
Game::createArrow(Point2D<float> reltvOrigin, Point2D<float> bowPos) {

	arrows.push_back(new flecha(bowPos + reltvOrigin, getTexture(ARROW), this));

}

// Recibe el rectángulo de la punta de la flecha y comprueba si explota globos.
bool Game::checkCollison(const Rectangle& tip) {
	int i = 0;
	bool enc = false;
	while(i < balloons.size() && !enc) { // Cada globo comprueba si choca.
		if (!balloons[i]->hit(tip)) ++i;
		else enc = true; // Si choca, deja de buscar.
	}

	return enc;
}
