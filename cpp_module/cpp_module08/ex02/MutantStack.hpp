
#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

		MutantStack() {}
		MutantStack(const MutantStack& ref);
		~MutantStack() {}
		MutantStack& operator=(const MutantStack& ref);

		iterator begin();
		iterator end();
};

template<typename T>
MutantStack<T>::MutantStack(const MutantStack& ref) {
	std::copy(ref.c.begin(), ref.c.end(), this->c.begin());
}

template<typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& ref) {
	std::copy(ref.c.begin(), ref.c.end(), this->c.begin());
}


template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return this->c.end();
}
