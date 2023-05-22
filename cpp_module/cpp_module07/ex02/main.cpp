
#include "Array.hpp"

int main() {
	{
		Array<int> a;
		Array<int> b(5);

		std::cout << a << std::endl;
		for (int i = 0; i < 5; i++)
			b[i] = i * 3;
		std::cout << b << std::endl;
	}
	{
		Array<char> a;
		Array<char> b(5);

		std::cout << a << std::endl;
		for (int i = 0; i < 5; i++)
			b[i] = 'a' + i * 3;
		std::cout << b << std::endl;
	}
	{
		Array<float> a;
		Array<float> b(5);

		std::cout << a << std::endl;
		for (int i = 0; i < 5; i++)
			b[i] = 0.5 + i * 3.7;
		std::cout << b << std::endl;
	}
	{
		Array<std::string> a;
		Array<std::string> b(5);

		std::cout << a << std::endl;
		b[0] = "hello";
		b[1] = "world";
		b[2] = "this";
		b[3] = "is";
		b[4] = "cpp";
		std::cout << b << std::endl;
	}
	{
		Array<int> a(3);

		try {
			a[5] = 100;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}


// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     //SCOPE
//     {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;
//     return 0;
// }
