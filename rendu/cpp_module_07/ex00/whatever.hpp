/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:18:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 11:32:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iomanip>
#include <iostream>

template <typename T>
void swap(T& arg1, T& arg2)
{
	T tmpArg;

	tmpArg = arg1;
	arg1 = arg2;
	arg2 = tmpArg;
};

template <typename T>
T min(T arg1, T arg2)
{
	if (arg1 < arg2)
		return (arg1);
	else
		return (arg2);
};

template <typename T>
T max(T arg1, T arg2)
{
	if (arg1 > arg2)
		return (arg1);
	else
		return (arg2);
};


#endif