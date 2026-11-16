#pragma once
#include "GameError.h"

class FileNotFoundError : public GameError
{
public:

	FileNotFoundError(string filename) : GameError("Error al buscar el archivo " + filename + ", no ha sido encontrado.") {};

};

