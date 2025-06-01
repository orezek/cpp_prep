/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:43:35 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/19 17:15:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"

bool StringUtils::digitsAndOneDotOnly(const std::string str)
{
	int	dots;

	dots = 0;
	for (std::string::size_type i = 0; i < str.size(); i++)
	{
		if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9'))
			return (false);
		if (str[i] == '.')
			dots++;
	}
	if (dots != 1)
		return (false);
	return (true);
}