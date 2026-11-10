// Juan José de Reyna Godoy y Camilo Sandoval Sánchez

// Esta subclase abstracta de GameObject se usará para objetos que estén presentes en la escena, es decir, una posición
// y dimensiones. Es abstracto porque tiene

#pragma once
#include "GameObject.h"
#include "rectangle.h"
#include "texture.h"

class Game;

class SceneObject: public GameObject
{
protected:

	Texture* text; // Puntero a la textura que se usará en el renderizado.

	int animIndex; // El índice de la fila en la matriz de frames.

	int frameIndex = 0; // El índice de la columna en la matriz de frames.

	Rectangle pos; // Rectángulo que contiene la posición en la escena del objeto, y en base al cual se renderizará este.

	float width; // Ancho del objeto.

	float height; // Alto del objeto.

	SceneObject(Game* myGame, Texture* myTexture, Point2D<float> myPos, float myWidht, float myHeight, int anim = 0) :
		GameObject(myGame),
		text(myTexture),
		width(myWidht),
		height(myHeight),
		pos(myPos, myWidht, myHeight),
		animIndex(anim)
	{
	};

public:

	~SceneObject() {
		text = nullptr;
	};

	void render() const override; // Renderiza un objeto en función de su rectángulo pos, con la textura text.

	virtual bool hit(const Rectangle&); // Devuelve true si hay colisión con el rectángulo pasado como parámetro.

};
