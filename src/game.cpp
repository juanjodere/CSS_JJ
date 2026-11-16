// Alterado por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>


#include "texture.h"
#include "Balloon.h"
#include "butterfly.h"

using namespace std;

// Constantes 
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";
constexpr const char* SAVE_ROOT = "../assets/savedgames/";

// tamaño que tendrán los objetos en la pantalla:
const float BOW_WIDTH = 90;
const float BOW_HEIGHT = 90;
const float BALLOON_WIDTH = 90;
const float BALLOON_HEIGHT = 90;
const float ARROW_WIDTH = 90;
const float ARROW_HEIGHT = 20;
const float BUTTERFLY_WIDTH = 90;
const float BUTTERFLY_HEIGHT = 20;
const float BUTTERFLY_VEL = 0.25;

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
	{"butterfly.png",4,10},
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

int numButterflies = 0;

bool partidaCargada = false;
bool btf = false;

// Cambia variables del game y otros elementos en base a un archivo en la carpeta LEVEL_ROOT.
// Relanza excepciones en caso de capturar alguna.
void Game::LoadLevel(const string& entrada) {
	ifstream guardado;
	guardado.open(LEVEL_ROOT + entrada); // Abre el archivo.

	if (!guardado.is_open()) throw FileNotFoundError(LEVEL_ROOT + entrada); // Excepción
	else {
		string clave = " ";
		while (!guardado.fail()) { // Mientras siga abierto.
			guardado >> clave;
			//cout << clave;
			if (clave[0] == '#') guardado.ignore('\n'); // Si es un comentario, ignora la línea.
			else if (clave == "bgcolor") {} // lee número de flechas.
			else if (clave == "arrows") { // lee número de flechas.
				int na = 0;
				guardado >> na;
				Jugador->setNumArrows(na);
				//guardado.ignore('\n');
			}
			else if (clave == "baldelay") guardado >> baldelay; // lee baldelay.
			else if (clave == "balpoints") ; // lee baldelay
			else if (clave == "balspeed"); // lee baldelay.
			else if (clave == "balgoal"); // lee baldelay.
			else if (clave == "butterflies") {
				guardado >> numButterflies;
			}
			else guardado.ignore('\n'); // Si no se sabe qué pone, se ignora la línea entera.
		}
	}

	guardado.close(); // Cierra el archivo.
}

// Construye el objeto Game e instancia un jugador.
// Relanza excepciones si captura alguna.
Game::Game()
  : exit(false), objects(), baldelay(12)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw new SDLError(); // Excepción

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
	throw new SDLError(); // Excepción

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
		throw FileNotFoundError(IMAGE_ROOT); // Excepción
	}
	// Crear los objetos del juego
	Jugador = new Arco(this, getTexture(BOW), { 0,250 }, BOW_WIDTH, BOW_HEIGHT, {0, 0.5});
	
	for (int i = 0; i < numButterflies; ++i) {
		Point2D<float> pos = { uniform_real_distribution<float>(100,100)(randomGenerator), uniform_real_distribution<float>(100, 100)(randomGenerator) };
		createButterfly(pos);
	}
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

	for (size_t i = 0; i < objects.size(); ++i) { // Borra las flechas que existiesen.
		delete objects[i];
		objects[i] = nullptr;
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

	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->render();
	}

	SDL_RenderPresent(renderer);
}

// Procesa los cambios de cada elemento.
void
Game::update(float dt)
{
	Jugador->update(dt); // El jugador realiza sus cambios de estado.

	for (int i = 0; i < objects.size(); ++i) { // Los globos realizan sus cambios de estado.
		bool active = objects[i]->update(dt);
		if (!active) { // Si debe borrar un globo, lo borra.
			delete objects[i];
			objects.erase(objects.begin() + i);
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

		initButterfly();

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

		const bool* keys = SDL_GetKeyboardState(nullptr); // Analiza teclado.
		if (keys[SDL_SCANCODE_LCTRL]) {
			if (keys[SDL_SCANCODE_S]) {
				saveGame();
			}
			else if (keys[SDL_SCANCODE_O]) {
				openGame();
			}
		}
	}
}

// Crea una mariposa y la mete al array de objetos.
void
Game::createButterfly(Point2D<float> origin) {
	Vector2D<float> vel = {float( uniform_int_distribution<int>(-1, 0)(randomGenerator) ) , float ( uniform_int_distribution<int>(-1, 0)(randomGenerator) )};
	if (vel.getX() == 0) vel = { 1, vel.getY() }; if (vel.getY() == 0) vel = { vel.getX(), 1 };

	objects.push_back(new butterfly(this, getTexture(BUTTERFLY), origin, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, { BUTTERFLY_VEL * vel.getX(), BUTTERFLY_VEL * vel.getY() }, 0));
}
// Crea una mariposa y la mete al array de objetos.
void
Game::initButterfly() {
	if (!btf) {
		for (int i = 0; i < numButterflies; ++i) {
			Point2D<float> pos = { uniform_real_distribution<float>(100,700)(randomGenerator), uniform_real_distribution<float>(100, 500)(randomGenerator) };
			createButterfly(pos);
		}
		btf = true;
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

	objects.push_back(new Balloon(this, getTexture(BALLOON), pos, BALLOON_WIDTH, BALLOON_HEIGHT, { 0, -speedVar }, color)); // Lo crea y mete al vector.
}

// Crea una flecha y la mete al vector de objetos..
void
Game::createArrow(Point2D<float> reltvOrigin, Point2D<float> bowPos) {

	objects.push_back( new flecha(this, getTexture(ARROW), bowPos + reltvOrigin, ARROW_WIDTH, ARROW_HEIGHT, {1, 0} ));

}

// Recibe el rectángulo de la punta de la flecha y comprueba si explota globos.
bool
Game::checkCollison(const Rectangle& tip) {
	int i = 0;
	bool enc = false;
	while(i < objects.size() && !enc) { // Cada globo comprueba si choca.
		if (typeid(*objects[i]) == typeid(Balloon)) {
			if (!objects[i]->hit(tip)) ++i;
			else enc = true; // Si choca, deja de buscar.
		}
		else i++;
	}

	return enc;
}

// Recibe el rectángulo de la punta de la flecha y comprueba si explota globos.
int
Game::getPoints() {

	return points;
}

// Recibe el rectángulo de la punta de la flecha y comprueba si explota globos.
void
Game::setPoints(int pts) {

	points += pts;
}

void
Game::saveGame() {
	ofstream juego;
	juego.open(SAVE_ROOT + string("partidaGuardada.txt"), std::ofstream::out | std::ofstream::trunc);

	if (!juego.is_open()) throw FileNotFoundError(SAVE_ROOT + string("partidaGuardada.txt")); // Excepción
	else {

		try {

			juego << "N " << Nivel << " P " << points << "\n";


			for (size_t i = 0; i < objects.size(); ++i) {
				objects[i]->saveObj(juego);
			}
		}
		catch (GameError error) {
			throw FileFormatError(SAVE_ROOT + string("partidaGuardada.txt"), 3);
		}
	}
	juego.close(); // Cierra el archivo.
}

void
Game::openGame() {
	ifstream juego;
	juego.open(SAVE_ROOT + string("partidaGuardada.txt")); // Abre el archivo.

	if (!juego.is_open()) throw new FileNotFoundError(SAVE_ROOT + string("partidaGuardada.txt")); // Excepción
	else {

		try {

			objects.clear();

			char clave = juego.get();
			//std::cout << clave;

			if (clave == 'N') {
				juego.get();
				string nivel;
				while (clave != ' ')
				{
					clave = juego.get();
					nivel += clave;
					//std::cout << clave;
				}
				Nivel = stoi(nivel);
			}
			//std::cout << clave;
			clave = juego.get();
			//std::cout << clave;
			if (clave == 'P') {
				juego.get();
				string pts;
				while (clave != ' ' && clave != '\n')
				{
					clave = juego.get();
					pts += clave;
				}
				points = stoi(pts);
				//std::cout << pts;
			}

			//std::cout << clave;
			while (!juego.fail()) { // Mientras siga abierto.
				clave = juego.get();
				if (clave == 'B') {
					objects.push_back(new Balloon(this, getTexture(BALLOON), juego));
					//std::cout << " Bya ";
				}
				else if (clave == 'A') {
					objects.push_back(new flecha(this, getTexture(ARROW), juego));
				}
				else if (clave == 'M') {
					objects.push_back(new butterfly(this, getTexture(BUTTERFLY), juego));
				}
				else juego.get();
			}
		}
		catch(GameError error){
			throw FileFormatError(SAVE_ROOT + string("partidaGuardada.txt"), 3);
		}
	}

	juego.close(); // Cierra el archivo.
	//std::cout << "open";
}
