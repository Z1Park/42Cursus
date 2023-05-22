
#include "easyfind.hpp"
#include <vector>
#include <queue>
#include <list>

int main() {
	{
		std::vector<int> v;
		v.push_back(5);
		v.push_back(2);
		v.push_back(9);
		v.push_back(-1);
		std::vector<int>::iterator found_vec1 = easyfind(v, 2);
		std::cout << *found_vec1 << std::endl;
		std::vector<int>::iterator found_vec2 = easyfind(v, -1);
		std::cout << *found_vec2 << std::endl;
		std::vector<int>::iterator found_vec3 = easyfind(v, 5);
		std::cout << *found_vec3 << std::endl;
		try {
			std::vector<int>::iterator found_vec4 = easyfind(v, 3);
			std::cout << *found_vec4 << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	{
		std::deque<int> q;
		q.push_back(5);
		q.push_back(2);
		q.push_back(9);
		q.push_back(-1);
		std::deque<int>::iterator found_vec1 = easyfind(q, 2);
		std::cout << *found_vec1 << std::endl;
		std::deque<int>::iterator found_vec2 = easyfind(q, -1);
		std::cout << *found_vec2 << std::endl;
		std::deque<int>::iterator found_vec3 = easyfind(q, 5);
		std::cout << *found_vec3 << std::endl;
		try {
			std::deque<int>::iterator found_vec4 = easyfind(q, 3);
			std::cout << *found_vec4 << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	{
		std::list<int> l;
		l.push_back(5);
		l.push_back(2);
		l.push_back(9);
		l.push_back(-1);
		std::list<int>::iterator found_vec1 = easyfind(l, 2);
		std::cout << *found_vec1 << std::endl;
		std::list<int>::iterator found_vec2 = easyfind(l, -1);
		std::cout << *found_vec2 << std::endl;
		std::list<int>::iterator found_vec3 = easyfind(l, 5);
		std::cout << *found_vec3 << std::endl;
		try {
			std::list<int>::iterator found_vec4 = easyfind(l, 3);
			std::cout << *found_vec4 << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}
