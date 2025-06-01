/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:43:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/19 17:12:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <iostream>
#include <string>

class StringUtils
{
	private:
		StringUtils();
		StringUtils(const StringUtils&);
		const StringUtils& operator=(const StringUtils&);
		~StringUtils();

	public:
		static bool digitsAndOneDotOnly(const std::string str);
};

#endif