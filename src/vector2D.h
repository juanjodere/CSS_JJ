// Alterado por Camilo Sandoval Sánchez y Juan José de Reyna Godoy.

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

/**
 * Vector bidimensional genérico.
 */
template<std::floating_point T = float>
class Vector2D
{
	T x, y;

public:
	Vector2D(T x, T y) : x(x), y(y) { }
	Vector2D() : Vector2D(0, 0) { }

	// Coordenadas del vector
	T getX() const { return x; }
	T getY() const { return y; }

	// Operadores
	Vector2D operator+(const Vector2D& otro) const {
		return {x + otro.x, y + otro.y};
	}
	Vector2D operator+=(const Vector2D& otro) {
		this->x += otro.x;
		this->y += otro.y;
		return *this;
	}
	Vector2D operator-(const Vector2D& otro) const {
		return { x - otro.x, y - otro.y };
	}
	Vector2D operator-=(const Vector2D& otro) {
		this->x -= otro.x;
		this->y -= otro.y;
		return *this;
	}
	Vector2D operator*(const float coef) {
		return { x * coef, y * coef };
	}
	Vector2D operator/(const float coef) {
		return { x / coef, y / coef };
	}

	// TODO: completar
	//T Lenght() const {
		//returns sqrt(pow(x, 2) + pow(y, 2));
	//}

	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}
};

// TODO: definir alias Point2D<T>
template<std::floating_point T = float>
using Point2D = Vector2D<T>;

#endif // VECTOR2D_H
