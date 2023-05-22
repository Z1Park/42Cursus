
#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

template<typename T>
typename T::iterator easyfind(T &container, int value) {
	typename T::iterator temp = find(container.begin(), container.end(), value);

	if (temp == container.end())
		throw std::runtime_error("The value is not in container");
	return temp;
}
