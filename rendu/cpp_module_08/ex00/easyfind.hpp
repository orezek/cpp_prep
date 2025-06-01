/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:30:11 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/30 10:45:01 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <exception>
#include <algorithm>

class ValueNotFound : public std::exception
{
	public:
		virtual const char *what() const throw();
};

const char* ValueNotFound::what() const throw() {
    return "Value not found in the container.";
}

template <typename T>
void	easyfind(const T& container, int num)
{
	typename T::const_iterator it;

	it = std::find(container.begin(), container.end(), num);

	if (it != container.end())
		std::cout << "Element '" << *it << "' was found." << std::endl;
	else
		throw ValueNotFound();
	return ;
}

#endif