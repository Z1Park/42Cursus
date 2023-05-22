
#include "iter.hpp"

int main() {
	{
		int array[5] = {924, 241, 2, 425, 99};
		::iter(array, 5, printValue);
	}
	{
		char array[5] = {'D', 'z', 'i', 'P', 'm'};
		::iter(array, 5, printValue);
	}
	{
		float array[5] = {19.23, 48.4, 32.9, 92.2, 10.7};
		::iter(array, 5, printValue);
	}
	{
		std::string array[5] = {"hello", "world", "this", "is", "cpp"};
		::iter(array, 5, printValue);
	}
	return 0;
}
