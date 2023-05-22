
#include "Span.hpp"

Span::Span() {
	std::cout << "Span default constructor is called" << std::endl;
}

Span::Span(unsigned int n) {
	std::cout << "Span default constructor is called" << std::endl;
	this->data.reserve(n);
}

Span::Span(const Span& ref) {
	std::cout << "Span copy constructor is called" << std::endl;
	if (this != &ref) {
		this->data.reserve(ref.data.capacity());
		std::copy(ref.data.begin(), ref.data.end(), data.begin());
	}
}

Span::~Span() {
	std::cout << "Span destructor is called" << std::endl;
}

Span&	Span::operator=(const Span& ref) {
	std::cout << "Span copy assignment operator is called" << std::endl;
	if (this != &ref) {
		this->data.reserve(ref.data.capacity());
		std::copy(ref.data.begin(), ref.data.end(), data.begin());
	}
	return *this;
}


void Span::addNumber(int num) {
	if (data.capacity() == data.size())
		throw addNumberException();
	data.push_back(num);
}

static int binary(const int &a) {
	return std::abs(a);
}

int Span::shortestSpan() {
	if (data.size() <= 1)
		throw spanException();
	std::vector<int> res(data);
	std::adjacent_difference(res.begin(), res.end(), res.begin());
	std::transform(res.begin(), res.end(), res.begin(), binary);
	return *(std::min_element(res.begin(), res.end()));
}

int Span::longestSpan() {
	if (data.size() <= 1)
		throw spanException();
	std::vector<int>::iterator v_max =  std::max_element(data.begin(), data.end());
	std::vector<int>::iterator v_min =  std::min_element(data.begin(), data.end());
	return *v_max - *v_min;
}

void Span::addRandomNumbers() {
	std::srand(std::time(NULL));
	while (data.size() < data.capacity())
		data.push_back(std::rand());
}


const char * Span::addNumberException::what() const throw() {
	return "Can not add number because Span is full";
};

const char * Span::spanException::what() const throw() {
	return "Can not span because there is one number in Span";
};
