
#pragma once
#include <iostream>

template<typename T>
void iter(T *array, unsigned int len, void (&iter_func)(T)) {
	for (unsigned int i = 0; i < len; i++) {
		iter_func(array[i]);
	}
}

template<typename T>
void printValue(T value) {
	std::cout << static_cast<T>(value) << std::endl;
}
