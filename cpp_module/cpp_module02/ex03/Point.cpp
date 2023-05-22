
#include "Point.hpp"

Point::Point() : x(0), y(0) {
}

Point::Point(const Fixed &x, const Fixed &y) : x(x), y(y) {
}

Point::Point(const Point &point) : x(point.x), y(point.y) {
}

Point::~Point() {
}

Point Point::operator=(Point &point) {
	const_cast<Fixed&>(x) = point.x;
	const_cast<Fixed&>(y) = point.y;
	return *this;
}

Point Point::operator-(const Point &point) const {
	return Point(x - point.getX(), y - point.getY());
}

Fixed Point::getX() const {
	return x;
}

Fixed Point::getY() const {
	return y;
}
