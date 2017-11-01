#include "Vector2.hpp"

using namespace std;


ostream& operator<<(ostream& stream, const Vector2& vec) {
	stream << "(" << vec.X() << ", " << vec.Y() << ")";
	return stream;
}

Vector2::Vector2(const float& x, const float& y) : x(x), y(y) {

}

Vector2 Vector2::operator+(const Vector2& vec) {
	Vector2 result;
	result.x = this->x + vec.x;
	result.y = this->y + vec.y;
	return result;
}

Vector2 Vector2::operator-(const Vector2& vec) {
	Vector2 result;
	result.x = this->x - vec.x;
	result.y = this->y - vec.y;
	return result;
}

Vector2 Vector2::operator*(const Vector2& vec) {
	Vector2 result;
	result.x = this->x * vec.x;
	result.y = this->y * vec.y;
	return result;
}

Vector2 Vector2::operator*(const float& scalar) {
	Vector2 result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	return result;
}

Vector2 Vector2::operator/(const Vector2& vec) {
	Vector2 result;
	result.x = (vec.x != 0 ? this->x / vec.x : 0);
	result.y = (vec.y != 0 ? this->y / vec.y : 0);
	return result;
}

const Vector2& Vector2::operator=(const Vector2& vec) {
	if (this != &vec) {
		this->x = vec.x;
		this->y = vec.y;
	}
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& vec) {
	this->x += vec.X();
	this->y += vec.Y();
	return *this;
}

float Vector2::X() const {
	return x;
}

float Vector2::Y() const {
	return y;
}

void Vector2::setPosition(const float& _x, const float& _y) {
	x = _x;
	y = _y;
}

void Vector2::setX(const float& _x) {
	x = _x;
}

void Vector2::setY(const float& _y) {
	y = _y;
}