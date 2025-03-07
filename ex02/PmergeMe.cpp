/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:31 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/07 12:13:45 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool PmergeMe::validateArgs() 
{
	int num;
	for(int i = 1; rawArgs[i] != NULL; i++)
	{
		try{
			num = std::stoi(rawArgs[i]);
			if (num < 0)
				return false;	
		}
		catch (const std::exception& e)
		{
			return false;
		}
	}
	return true;
}

PmergeMe::PmergeMe(char **argv) : rawArgs((const char**)argv)
{
	std::cout << validateArgs() << std::endl;
}

PmergeMe::~PmergeMe()
{
}
