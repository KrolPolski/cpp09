/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:31 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/11 13:26:49 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::sortPairsInPlace()
{
	for (unsigned int i = 0; i + 1 < vecSorted.size(); i += 2)
	{
		if (vecSorted[i] > vecSorted[i + 1])
		{
			int tmp = vecSorted[i];
			vecSorted[i] = vecSorted[i + 1];
			vecSorted[i + 1] = tmp;
		}
		else
		{
			std::cout << vecSorted[i] << " must be less than or equal to " << vecSorted[i+1] << std::endl;
		}
	}
}

void PmergeMe::vecSort(unsigned int elem_size)
{
	auto iter = vecSorted.begin();
	unsigned int k;
	
	for (unsigned int i = 0; i * elem_size < vecSorted.size(); i += 2)
	{
		k = i * elem_size;
		if (k + elem_size < vecSorted.size() && vecSorted[k] > vecSorted[k + elem_size])
		{
			std::swap_ranges(iter + k, iter + k + elem_size, iter + k + elem_size);
		}
	}
	std::cout << "iteration: ";
	for (unsigned int l = 0; l < vecSorted.size(); l++)
		std::cout << vecSorted[l] << " ";
	std::cout << std::endl;
	if (elem_size * 2 <= vecSorted.size())
		vecSort(elem_size * 2);
}
bool PmergeMe::validateArgs() 
{
	int num;
	for(int i = 1; i < _argc; i++)
	{
		try{
			num = std::stoi(rawArgs[i]);
			if (num < 0)
				return false;	
			else vecUnsorted.push_back(num);
		}
		catch (const std::exception& e)
		{
			return false;
		}
	}
	return true;
}

PmergeMe::PmergeMe(char **argv, int argc) :  _argc(argc), rawArgs((const char**)argv)
{
	validateArgs();
	vecSorted = vecUnsorted;
	std::cout << "Unsorted vector: ";  
	for (unsigned int i = 0; i < vecUnsorted.size(); i++)
		std::cout << vecUnsorted[i] << ", ";
	std::cout << std::endl;
	vecSort(1);
	//sortPairsInPlace();
	std::cout << "Pairs sorted: ";  
	for (unsigned int i = 0; i < vecUnsorted.size(); i++)
		std::cout << vecSorted[i] << ", ";
	std::cout << std::endl;
}
PmergeMe::~PmergeMe()
{
}
