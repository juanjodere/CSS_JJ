#pragma once
#include "GameError.h"

class FileFormatError : public GameError
{
public:

	FileFormatError(string filename, int line) : GameError("Formato no esperado en el archivo " + filename + " en la línea " + std::to_string(line) + ".") {};

};
