
#pragma once
#include <iostream>
#include <string>
#include <exception>

template<class T>
class Array {
	private:
		T *arr;
		unsigned int _size;

	public:
		Array();
		Array(unsigned int arr_size);
		Array(const Array& ref);
		~Array();
		Array<T>& operator=(const Array& ref);

		class IndexingException : public std::exception {
			const char * what() const throw();
		};

		unsigned int size();
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;
};

template<class T>
Array<T>::Array() {
	arr = new T[0];
	_size = 0;
}

template<class T>
Array<T>::Array(unsigned int arr_size) : _size(arr_size) {
	this->arr = new T[_size];
}

template<class T>
Array<T>::Array(const Array& ref) {
	this->_size = ref._size;
	this->arr = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		this->arr[i] = ref.arr[i];
}

template<class T>
Array<T>::~Array() {
	delete[] arr;
}

template<class T>
Array<T>&	Array<T>::operator=(const Array& ref) {
	if (this != &ref) {
		delete[] this->arr;
		this->_size = ref._size;
		this->arr = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			this->arr[i] = ref.arr[i];
	}
	return *this;
}

template<class T>
const char * Array<T>::IndexingException::what() const throw() {
	return "index is over array size";
}

template<class T>
unsigned int Array<T>::size() {
	return this->_size;
}

template<class T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= _size)
		throw IndexingException();
	return arr[index];
}

template<class T>
const T& Array<T>::operator[](unsigned int index) const {
	if (index >= _size)
		throw IndexingException();
	return arr[index];
}

template<class T>
std::ostream& operator<<(std::ostream &os, Array<T> &arr) {
	os << "array size : " << arr.size() << std::endl;
	for (unsigned int i = 0; i < arr.size(); i++)
		os << "array[" << i << "] : " << arr[i] << std::endl;
	return os;
}
