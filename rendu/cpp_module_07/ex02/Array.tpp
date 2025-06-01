/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:44:24 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 13:45:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T> Array<T>::Array()
{
	this->data = NULL;
	this->arrSize = 0;
};

template <typename T> Array<T>::Array(unsigned int n)
{
	this->data = new T[n];
	arrSize = n;
};

template <typename T> Array<T>::Array(const Array& refArray)
{
	this->arrSize = refArray.size();
	this->data = new T[refArray.size()];
	for (unsigned int i = 0; i < this->size(); i++)
		this->data[i] = refArray.data[i];
};

template <typename T> Array<T>& Array<T>::operator=(const Array& refArray)
{
	if (this != &refArray)
	{
		delete[] this->data;
		this->arrSize = refArray.size();
		this->data = new T[refArray.size()];
		for (unsigned int i = 0; i < this->size(); i++)
			this->data[i] = refArray.data[i];
	}
	return (*this);
};

template <typename T> Array<T>::~Array() { delete[] this->data; };

template <typename T> unsigned int Array<T>::size() const
{
	return (this->arrSize);
};

template <typename T> T& Array<T>::operator[](unsigned int index)
{
	if (index >= this->arrSize)
	{
		throw std::out_of_range("Index out of range");
	}
	return data[index];
};