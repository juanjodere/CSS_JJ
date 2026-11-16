

#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
using namespace std;

class Game;

class InfoBar: public GameObject
{
protected:
	string textPts;
	string renderTxt;
	string ptsUI;
	InfoBar(Game* game) :
		GameObject(game),
		textPts("Puntos obtenidos: ") 
	{};

public:
	
	void render() const override;

	bool update(float dt) override;
};

