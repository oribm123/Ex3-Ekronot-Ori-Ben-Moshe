#include "Vector.h"
#include <iostream>

#define MIN_CAP 2
#define EMPTY -9999

Vector::Vector(int n) {
	if (n < MIN_CAP) {
		n = MIN_CAP;
	}
	this->_elements = new int[n];
	this->_size = 0;
	this->_capacity = n;
	this->_resizeFactor = n;
}

Vector::~Vector() {
	delete[] this->_elements;
}

int Vector::size() const {
	return this->_size;
}

int Vector::capacity() const {
	return this->_capacity;
}

int Vector::resizeFactor() const {
	return this->_resizeFactor;
}

bool Vector::empty() const {
	return this->_size == 0;
}

void Vector::push_back(const int& val) {
	if (this->_size == _capacity) {
		reserve(this->_capacity + this->_resizeFactor);
	}
	this->_elements[this->_size++] = val;
}

int Vector::pop_back() {
	if (empty()) {
		std::cerr << "error: pop from empty vector" << std::endl;
		return EMPTY;
	}
	return this->_elements[--this->_size];
}

void Vector::reserve(const int n) {
	if (n > this->_capacity) {
		int newCapacity = ((n + this->_resizeFactor - 1) / this->_resizeFactor) * this->_resizeFactor; // rounds it to the smallest multiple of the factor that is bigger than n
		int* newElements = new int[newCapacity];
		for (int i = 0; i < this->_size; i++) {
			newElements[i] = this->_elements[i];
		}
		delete[] this->_elements;
		this->_elements = newElements;
		this->_capacity = newCapacity;
	}
}

void Vector::resize(int n) {
	if (n > this->_capacity) {
		reserve(n); 
	}
	this->_size = n;
}

void Vector::assign(const int val) {
	for (int i = 0; i < this->_size; i++) {
		this->_elements[i] = val;
	}
}

void Vector::resize(const int n, const int& val) {
	if (n > this->_capacity) reserve(n);
	for (int i = this->_size; i < n; i++) {
		this->_elements[i] = val;
	}
	this->_size = n;
}

Vector::Vector(const Vector& other) {
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;
	this->_elements = new int[_capacity];
	for (int i = 0; i < this->_size; i++) {
		this->_elements[i] = other._elements[i];
	}
}

Vector& Vector::operator=(const Vector& other) {
	if (this == &other) {
		return *this;
	}
	delete[] this->_elements;
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;
	this->_elements = new int[_capacity];
	for (int i = 0; i < this->_size; i++) {
		this->_elements[i] = other._elements[i];
	}
	return *this;
}

int& Vector::operator[](int n) const {
	if (n >= this->_size || n < 0) {
		std::cerr << "Error: index out of bounds. returning the first element" << std::endl;
		return this->_elements[0];
	}
	return this->_elements[n];
}

Vector& Vector::operator+=(const Vector& other) {
	int min;
	if (this->_size < other._size) {
		min = this->_size;
	}
	else {
		min = other._size;
	}

	for (int i = 0; i < min; ++i) {
		this->_elements[i] += other._elements[i];
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& other) {
	int min;
	if (this->_size < other._size) {
		min = this->_size;
	}
	else {
		min = other._size;
	}

	for (int i = 0; i < min; ++i) {
		this->_elements[i] -= other._elements[i];
	}
	return *this;
}