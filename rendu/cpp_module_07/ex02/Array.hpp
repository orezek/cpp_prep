/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:32:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 13:11:46 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T>
class Array
{
	private:
		T*				data;
		unsigned int	arrSize;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array& refArray);
		Array& operator=(const Array& refArray);
		~Array();

		unsigned int size() const;
		T& operator[](unsigned int index);
		// const T& operator[](std::size_t index) const;
};

#include "Array.tpp"

#endif