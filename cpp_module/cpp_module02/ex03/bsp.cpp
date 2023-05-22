
#include "Point.hpp"

Fixed cross_product(const Point p1, const Point p2, const Point point) {
	Point cast_p1 = const_cast<Point&>(p1);
	Point cast_p2 = const_cast<Point&>(p2);
	Point cast_point = const_cast<Point&>(point);
	Point tmp1 = point - cast_p1;
	Point tmp2 = point - cast_p2;
	Fixed tmp = (tmp1.getX() * tmp2.getY() - tmp2.getX() * tmp1.getY());
	return tmp;
}

bool bsp(const Point a, const Point b, const Point c, const Point point) {
	Fixed ab = cross_product(a, b, point);
	Fixed bc = cross_product(b, c, point);
	Fixed ca = cross_product(c, a, point);

	return ab * bc > 0 && bc * ca > 0 && ca * ab > 0;
}
