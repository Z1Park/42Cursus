
#include <stdlib.h>
#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) {
	Point arr[4];
	srand(time(NULL));

	while (1)
	{
		for (int i = 0; i < 4; i++) {
			Fixed x = Fixed(rand() % 10);
			Fixed y = Fixed(rand() % 10);
			Point p(x, y);
			arr[i] = p;
			for (int j = 0; j < i; j++) {
				if (arr[j].getX() == arr[i].getX() && arr[j].getY() == arr[i].getY())
					i--;
			}
		}
		if (bsp(arr[0], arr[1], arr[2], arr[3]))
			break;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == arr[0].getX().toInt() && j == arr[0].getY().toInt()) std::cout << "*";
			else if (i == arr[1].getX().toInt() && j == arr[1].getY().toInt()) std::cout << "*";
			else if (i == arr[2].getX().toInt() && j == arr[2].getY().toInt()) std::cout << "*";
			else if (i == arr[3].getX().toInt() && j == arr[3].getY().toInt()) std::cout << "o";
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
