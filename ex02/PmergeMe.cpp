/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:31 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/02 15:51:30 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*void PmergeMe::sortPairsInPlace()
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
}*/
int PmergeMe::binarySearchNthElement(const std::vector<int>& mainChain, int target, int elemSize)
{
	//unsigned int offset = elemSize - 1;
	//unsigned int totalElements = mainChain.size() / elemSize;
	int left = 0;
	int mid = 0;
	int right = (mainChain.size() - 1) / elemSize * elemSize;
	while (left <= right) 
	{
		mid = left + (right - left) / (2 * elemSize) * elemSize;
		if (mainChain[mid] == target)
		{
			vecComparisons++;
			return mid;
		}
		if (mainChain[mid] < target)
		{
			vecComparisons++;
			left = mid + elemSize;
		}
		else
			right = mid - elemSize;
	}
	return mid;	
}

void PmergeMe::complexInsert(std::vector<int>& mainChain, std::vector<int>& pendChain)
{
	// If we get here we know we are at an element size of 1 and are doing the final insertions.
	// This is where we will use the Jacobsthal numbers.
	// for now:
	//unsigned int currJacobsthal = 3;
	//unsigned int prevJacobsthal = 1;
		
	std::cout << "Hello from complexInsert!" << std::endl;
	std::cout << "Main chain: ";
	for (unsigned int i = 0; i < mainChain.size(); i++)
		std::cout << mainChain[i] << " ";
	std::cout << std::endl;
	std::cout << "pendChain: ";
	for (unsigned int i = 0; i < pendChain.size(); i++)
		std::cout << pendChain[i] << " ";
	std::cout << std::endl;
		
}
void PmergeMe::binaryInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize, int nonParticipants)
{
	std::cout << "Begin binary insertion woo" << std::endl;
	auto iter = mainChain.begin();
	if (elemSize - 1 < pendChain.size())
	{
		std::cout << "Main chain ";
		for (unsigned int i = 0; i < mainChain.size(); i++)
			std::cout << mainChain[i] << " ";
		std::cout << std::endl;
		std::cout << "Pending chain ";
		for (unsigned int i = 0; i < pendChain.size(); i++)
			std::cout << pendChain[i] << " ";
		std::cout << std::endl;
		std::cout << "We think first insertion should be based on pendChain[" << elemSize -1 << "] which is " << pendChain[elemSize - 1] << std::endl;
		int mid = binarySearchNthElement(mainChain, pendChain[elemSize - 1], elemSize);
		std::cout << "We think it should be inserted at mainChain[" << mid << "]" << std::endl;  
		std::cout << "Non participants begin at: " << nonParticipants  << std::endl;
		auto pendIter = pendChain.begin();
		mainChain.insert(iter + mid, pendIter, pendIter + elemSize);
		std::cout << "After insertion mainChain is now: ";
		for (unsigned int i = 0; i < mainChain.size(); i++)
			std::cout << mainChain[i] << " ";
		std::cout << std::endl;
		std::cout << "Now overwriting vecSorted " << std::endl;
		for (unsigned int i = 0; i < mainChain.size(); i++)
		{
			vecSorted[i] = mainChain[i];
		}
	}
}

void PmergeMe::vecSort(unsigned int elem_size)
{
	auto iter = vecSorted.begin();
	unsigned int k;
	unsigned int offset;
	for (unsigned int i = 0; i * elem_size < vecSorted.size(); i += 2)
	{
		k = i * elem_size;
		offset = elem_size - 1;
		if (k + elem_size + offset < vecSorted.size())
		{ 
			if(vecSorted[k + offset] > vecSorted[k + elem_size + offset])
			{
				std::swap_ranges(iter + k, iter + k + elem_size, iter + k + elem_size);
			}
			vecComparisons++;
		}
	}
	std::cout << "iteration: ";
	for (unsigned int l = 0; l < vecSorted.size(); l++)
		std::cout << vecSorted[l] << " ";
	std::cout << std::endl;
	if (elem_size * 2 <= vecSorted.size())
		vecSort(elem_size * 2);
	if (elem_size > 1)
	{
		std::vector<int> mainChain(vecSorted.begin(), vecSorted.begin()+ k);
		std::cout << "For element size: " << elem_size << " the main chain is: " << std::endl;
		for (unsigned int i = 0; i < mainChain.size(); i++)
			std::cout << mainChain[i] << " ";
		std::cout << std::endl;
		std::vector<int> pendChain;
		int nonParticipants = k + elem_size < vecSorted.size() ? k + elem_size : -1;
		if (k > 0 && k + offset < vecSorted.size())
		{
			std::cout << "k is " << k << " and len is " << vecSorted.size() << " so we have a leftover element" << std::endl;
			std::cout << "Leftover element is ";
			for (unsigned int a = k; a < vecSorted.size() && a < k + elem_size; a++)
			{
				std::cout << vecSorted[a] << " ";
				pendChain.push_back(vecSorted[a]);
			}		
			std::cout << std::endl;
			// so we have leftover element that starts at vecSorted[k] and goes until k + elem_size -1
			// that will need to be inserted based on vecSorted[k + offset]
			std::cout << "pendChain is: ";
			for (unsigned int i= 0; i < pendChain.size(); i++)
				std::cout << pendChain[i] << " ";
			std::cout << std::endl;
		}
		std::cout << "Non participants identified at index: " << nonParticipants << std::endl;
		binaryInsert(mainChain, pendChain, elem_size, nonParticipants);
	}
	else
	{
		
		std::vector<int> mainChain;
		mainChain.push_back(vecSorted[0]);
		for (unsigned int i = 1; i < vecSorted.size(); i += 2)
			mainChain.push_back(vecSorted[i]);
		std::vector<int> pendChain;
		for (unsigned int i = 2; i < vecSorted.size(); i += 2)
			pendChain.push_back(vecSorted[i]);
		// We have to change the way these chains get built for the final case.
		// we start from b3, do b2, then b5, b4, etc.
		// use jacobsthal sequence until there aren't enough elements. 
		// then just binary insertion.

		complexInsert(mainChain, pendChain);
	}
	// we need a way to flag nonparticipants;
		// now we need to insert the pendChain
	/*unsigned int pendLen = pendChain.size() / elem_size;
	unsigned int currentJacobsthal = jacobsthalNumber(pendLen);
	unsigned int previousJacobsthal;
	std::cout << "currentJacobsthal: " << currentJacobsthal << std::endl;*/
	//if (pendLen > 0)
	//{
	//	previousJacobsthal = jacobsthalNumber(pendLen - 1);
//	}
	//else
	//	previousJacobsthal = 1;
	//std::cout << "previousJacobsthal: " << previousJacobsthal << std::endl;
	//unsigned int numInsertedElements = currentJacobsthal - previousJacobsthal;
	//std::cout << "numInsertedElements: " << numInsertedElements << std::endl;
	// not sure how this helps at all. but here is the failsafe:
	// 
}

unsigned int PmergeMe::jacobsthalNumber(unsigned int n)
{
	// starts with 0 and 1, then we add the previous number plus double the number before that
	// and we skip the first two to match the book
	if (n == 0)
		return 1;
	std::vector<unsigned int> jacobsthalNums(n + 1);
	jacobsthalNums[0] = 1;
	jacobsthalNums[1] = 3;
	//std::cout << "Jacobsthal sequence: ";
	//std::cout << jacobsthalNums[0] << " " << jacobsthalNums[1] << " ";
	for (unsigned int i = 2; i <= n; i++)
	{
		jacobsthalNums[i] = jacobsthalNums[i-1] + (2 * jacobsthalNums[i - 2]);
		//std::cout << jacobsthalNums[i] << " ";
	}
	//std::cout << std::endl;
	return jacobsthalNums[n];
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
	std::cout << "vecComparisons so far: " << vecComparisons << std::endl;
}
PmergeMe::~PmergeMe()
{
}
