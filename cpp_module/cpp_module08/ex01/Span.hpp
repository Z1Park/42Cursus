
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <numeric>
#include <stdlib.h>

class Span {
	private:
		std::vector<int> data;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span& ref);
		~Span();
		Span&	operator=(const Span& ref);

		void addNumber(int num);
		int shortestSpan();
		int longestSpan();
		void addRandomNumbers();

		class addNumberException : public std::exception {
			const char * what() const throw();
		};
		class spanException : public std::exception {
			const char * what() const throw();
		};
};
