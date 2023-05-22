#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"

int main() {
	clock_t start, finish;
	{
		std::vector<int> v;
		std::map<int, int> m;
		std::set<int> s;

		std::cout << "==================== std test ====================" << std::endl;
		std::cout << "vector test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			v.push_back(i);
		m.clear();
		finish = clock();
		std::cout << "vector test done" << std::endl;
		std::cout << "std::vector time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl;

		std::cout << "map test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			m.insert(std::make_pair(i, i * 3));
		m.clear();
		finish = clock();
		std::cout << "map test done" << std::endl;
		std::cout << "std::map time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl;

		std::cout << "set test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			s.insert(i);
		s.clear();
		finish = clock();
		std::cout << "set test done" << std::endl;
		std::cout << "std::set time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl;
	}
	{
		ft::vector<int> v;
		ft::map<int, int> m;
		ft::set<int> s;

		std::cout << "==================== ft test ====================" << std::endl;
		std::cout << "vector test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			v.push_back(i);
		m.clear();
		finish = clock();
		std::cout << "vector test done" << std::endl;
		std::cout << "std::vector time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl;

		std::cout << "map test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			m.insert(ft::make_pair(i, i * 3));
		m.clear();
		finish = clock();
		std::cout << "map test done" << std::endl;
		std::cout << "ft::map time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl;

		std::cout << "set test start" << std::endl;
		start = clock();
		for (int i = 0; i < 2000000; i++)
			s.insert(i);
		s.clear();
		finish = clock();
		std::cout << "set test done" << std::endl;
		std::cout << "ft::set time : " << (double)(finish - start) / CLOCKS_PER_SEC << std::endl;
	}
}
