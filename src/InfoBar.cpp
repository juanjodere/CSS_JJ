#include "InfoBar.h"
#include "game.h"

void InfoBar::render() const {

	//bool TTF_DrawRendererText(TTF_Text * text, float x, float y);
}

bool InfoBar::update(float dt) {
	ptsUI = to_string(GameObject::_game->getPoints());
	renderTxt = (textPts + ptsUI);
	return true;
}
