#pragma once

#include <iostream>

template <typename T>
class Array
{
	private:
		T*				_array;
		unsigned int	_size;

	public:
        // default constructor
		Array() : _size(0) {
        	this->_array = new T[this->_size];
		};
        // constructor
		Array(unsigned int size) : _size(size) {
			this->_array = new T[this->_size];
		};
        // copy constructor
		Array(const Array& other) : _size(other.size()) {
			this->_array = new T[_size];
			for (unsigned int i = 0; i < _size; ++i)
				this->_array[i] = other._array[i];
		};
        // assignment operator
		Array& operator=(const Array& other) {
			if (this != &other)
			{
				delete[] this->_array;
				this->_size = other.size();
				this->_array = new T[other.size()];
				for (unsigned int i = 0; i < this->size(); i++)
					this->_array[i] = other._array[i];
			}
			return (*this);
		};
        // destructor
		~Array() {
			if (this->_array != NULL) {
				delete [] this->_array;
			}
		};
		// getSize getter
		unsigned int size() const {
			return this->_size;
		};
        // subscript operator []
		T& operator[](unsigned int index) {
			if (index >= this->_size || this->_array == NULL)
			{
				std::cout << "index: " << index << std::endl;
				throw Array<T>::InvalidIndexException();
			}
			return (this->_array[index]);
		};
		// exception class
		class InvalidIndexException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "Array: invalid index";
			}
		};

};
