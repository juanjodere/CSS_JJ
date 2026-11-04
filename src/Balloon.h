// Hecho por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#pragma once

#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"


constexpr float WIDTH = 90;//const
constexpr float HEIGHT = 90;//const
// Tiempo que pasa entre un frame y otro en la animación de destruir.
constexpr float CICLES_BETWEEN_FRAMES = 150;

class Balloon
{
private:
	// Puntero a la textura.
	Texture* textura;

	// Posicion y dimesiones.
	Rectangle pos;

	//Color
	int colorIndex;
	
	// Velocidad de movimiento.
	Vector2D<float> vel;

	// Indice del frame en la animación de destrucción.
	int indice;//const

	// Detecta el estado del globo.
	bool explotado;

	// Guarda el tiempo actual de la animación de destrucción.
	float ciclAnimAct = CICLES_BETWEEN_FRAMES;

public:

	Balloon(Point2D<float> pos, Vector2D<float> vel, int color, Texture* textr, int arrayIndex) :
		colorIndex(color),
		textura(textr),
		pos(pos, WIDTH, HEIGHT),
		indice(arrayIndex),
		vel(vel),
		explotado(false)
	{};

	bool hit(const Rectangle&);

	void render() const;

	void move(int dt);

	bool update(int dt);

	bool popBalloon();
};

