
#pragma once
#include <iostream>
#include "Fixed.hpp"

class Point {
	private:
		const Fixed x;
		const Fixed y;

	public:
		Point();
		Point(const Fixed &x, const Fixed &y);
		Point(const Point &point);
		~Point();
		Point operator=(Point &point);
		Point operator-(const Point &point) const;

		Fixed getX() const;
		Fixed getY() const;
};

bool bsp(const Point a, const Point b, const Point c, const Point point);
