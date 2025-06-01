/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:56:40 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/24 12:23:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer& refObj) { *this = refObj; }
const Serializer& Serializer::operator=(const Serializer& refObj) { (void) refObj; return(*this); }
Serializer::~Serializer() {};

// reinterpret_cast< target-type >( expression )
// - Returns a value of type target-type.
// - It is primarily a compile-time directive which instructs the compiler to treat expression as if it had the type target-type.
// - More info: https://en.cppreference.com/w/cpp/language/reinterpret_cast


uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
};


Data* Serializer::deserialize(uintptr_t raw) 
{
	return (reinterpret_cast<Data*>(raw));
};
