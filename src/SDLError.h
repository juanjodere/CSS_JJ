#pragma once
#include "GameError.h"
#include <SDL3/SDL_error.h>

class SDLError : public GameError
{
public:

	SDLError() : GameError(SDL_GetError()) {};

};

