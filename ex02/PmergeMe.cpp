/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:31 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/05 14:07:16 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

unsigned int PmergeMe::countUnprocessed(std::vector<bool>& processed)
{
	unsigned int unProcessed {0};
	for (size_t i = 0; i < processed.size(); i++)
	{
		if (!processed[i])
			unProcessed++;
	}
	return unProcessed;
}

void PmergeMe::vectorMultiInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize)
{
	std::vector<bool> processed(pendChain.size(), false); // this keeps track of what has already been inserted.
	
	unsigned int jacobsthalN = 1;
	unsigned int currJacobsthal = jacobsthalNumber(jacobsthalN); // applies to two indexes less than itself because
	// b1 was already inserted into main chain and then because we count from 0.
	unsigned int prevJacobsthal = jacobsthalNumber(jacobsthalN - 1);
	while (currJacobsthal - 2 < pendChain.size() / elemSize)
	{
		int currIndex = currJacobsthal - 2;
		if (currIndex < 0)
			break;
		int insertionCount = currJacobsthal - prevJacobsthal;
		while (insertionCount > 0 && currIndex >= 0)
		{
			int sortValueIndex = currIndex * elemSize + elemSize - 1;
			int actualPendIndex = currIndex * elemSize;
			if (sortValueIndex < 0)
				break;
			if ((size_t)sortValueIndex >= pendChain.size() && pendChain.size() < elemSize)
				break ;
			if ((size_t)sortValueIndex >= pendChain.size())
			{
				sortValueIndex = elemSize - 1;
				actualPendIndex = 0;
			}
				auto iter = partial_lower_bound(mainChain.begin(), mainChain.end(), pendChain[sortValueIndex], elemSize);
		 		mainChain.insert(iter, pendChain.begin() + actualPendIndex, pendChain.begin() + actualPendIndex + elemSize);
		 		for (size_t i = 0; i < elemSize; i++)
					processed[actualPendIndex + i] = true;
		 	
		insertionCount--;
		currIndex--;
		}
		prevJacobsthal = currJacobsthal;
		jacobsthalN++;
		currJacobsthal = jacobsthalNumber(jacobsthalN);
	}
	// now we have to account for extra insertions if required (if we have complete elements left after
	// doing jacobsthal insertions)
	while (countUnprocessed(processed) >= elemSize)
	{
		int firstUnprocessedIndex {0};
		for (size_t i = 0; i < processed.size(); i++)
		{
			if (!processed[i])
			{
				firstUnprocessedIndex = i;
				break ;
			}
		}
		int sortableIndex = firstUnprocessedIndex + elemSize - 1;
		auto iter = partial_lower_bound(mainChain.begin(), mainChain.end(), pendChain[sortableIndex], elemSize);
		mainChain.insert(iter, pendChain.begin() + firstUnprocessedIndex, pendChain.begin() + firstUnprocessedIndex + elemSize);
		for (size_t i = 0; i < elemSize; i++)
			processed[firstUnprocessedIndex + i] = true;
	}
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		vecSorted[i] = mainChain[i];
	}
}

void PmergeMe::vecSort(unsigned int elemSize)
{
	auto iter = vecSorted.begin();
	unsigned int k;
	unsigned int offset;
	for (unsigned int i = 0; i * elemSize < vecSorted.size(); i += 2)
	{
		k = i * elemSize;
		offset = elemSize - 1;
		if (k + elemSize + offset < vecSorted.size())
		{ 
			if(vecSorted[k + offset] > vecSorted[k + elemSize + offset])
			{
				std::swap_ranges(iter + k, iter + k + elemSize, iter + k + elemSize);
			}
		}
	}
	if (elemSize * 2 <= vecSorted.size())
		vecSort(elemSize * 2);
	if (elemSize > 1)
	{
		if (vecSorted.size() / elemSize > 2)
		{
		std::vector<int> mainChain(vecSorted.begin(), vecSorted.begin() + elemSize * 2);
		std::vector<int> pendChain;
		if ((vecSorted.size() / elemSize) % 2 == 0)
		{ 
			for (unsigned int n = 3; (n + 2) * elemSize < vecSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					mainChain.push_back(vecSorted[n * elemSize + i]);
				}
			}
			for (unsigned int n = 2; (n + 1) * elemSize < vecSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(vecSorted[n * elemSize + i]);
				}
			}
			unsigned int n = (vecSorted.size() / elemSize) - 1;
			if ((n + 1) * elemSize < vecSorted.size())
			{	
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(vecSorted[n * elemSize + i]);
				}
			}
		}
		else
		{
			for (unsigned int n = 3; (n + 1) * elemSize < vecSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					mainChain.push_back(vecSorted[n * elemSize + i]);
				}
			}
			for (unsigned int n = 2; (n) * elemSize < vecSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(vecSorted[n * elemSize + i]);
				}
			}
		}
		vectorMultiInsert(mainChain, pendChain, elemSize);
		}
	}
	else
	{
		std::vector<int> mainChain;
		mainChain.push_back(vecSorted[0]);
		std::vector<int> pendChain;
		if ((vecSorted.size() / elemSize) % 2 == 0)
		{
			for (unsigned int i = 1; i < vecSorted.size() - 2; i += 2)
				mainChain.push_back(vecSorted[i]);
			for (unsigned int i = 2; i < vecSorted.size(); i += 2)
				pendChain.push_back(vecSorted[i]);
			pendChain.push_back(vecSorted[vecSorted.size() - 1]);
		}
		else
		{
			for (unsigned int i = 1; i < vecSorted.size(); i += 2)
				mainChain.push_back(vecSorted[i]);
			for (unsigned int i = 2; i < vecSorted.size(); i += 2)
				pendChain.push_back(vecSorted[i]);
		}
		vectorMultiInsert(mainChain, pendChain, elemSize);
	}
}

unsigned int PmergeMe::jacobsthalNumber(unsigned int n)
{
	// starts with 0 and 1, then we add the previous number plus double the number before that
	// and we skip the first two to match the book referenced in the subject
	if (n == 0)
		return 1;
	std::vector<unsigned int> jacobsthalNums(n + 1);
	jacobsthalNums[0] = 1;
	jacobsthalNums[1] = 3;
	for (unsigned int i = 2; i <= n; i++)
	{
		jacobsthalNums[i] = jacobsthalNums[i-1] + (2 * jacobsthalNums[i - 2]);
	}
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
			{
				std::cerr << "ERROR: Only positive integers accepted" << std::endl;
				return false;
			}		
			else
			{ 
				vecUnsorted.push_back(num);
				dequeUnsorted.push_back(num);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR: " << e.what() << " cannot convert argv["<< i << "]: " << rawArgs[i] << std::endl;
			return false;
		}
	}
	return true;
}

#include "PmergeMe.hpp"

unsigned int PmergeMe::countUnprocessed(std::deque<bool>& processed)
{
	unsigned int unProcessed {0};
	for (size_t i = 0; i < processed.size(); i++)
	{
		if (!processed[i])
			unProcessed++;
	}
	return unProcessed;
}

void PmergeMe::dequeMultiInsert(std::deque<int>& mainChain, std::deque<int>& pendChain, unsigned int elemSize)
{
	std::deque<bool> processed(pendChain.size(), false); // this keeps track of what has already been inserted.
	
	unsigned int jacobsthalN = 1;
	unsigned int currJacobsthal = jacobsthalNumber(jacobsthalN); // applies to two indexes less than itself because
	// b1 was already inserted into main chain and then because we count from 0.
	unsigned int prevJacobsthal = jacobsthalNumber(jacobsthalN - 1);
	while (currJacobsthal - 2 < pendChain.size() / elemSize)
	{
		int currIndex = currJacobsthal - 2;
		if (currIndex < 0)
			break;
		int insertionCount = currJacobsthal - prevJacobsthal;
		while (insertionCount > 0 && currIndex >= 0)
		{
			int sortValueIndex = currIndex * elemSize + elemSize - 1;
			int actualPendIndex = currIndex * elemSize;
			if (sortValueIndex < 0)
				break;
			if ((size_t)sortValueIndex >= pendChain.size() && pendChain.size() < elemSize)
				break ;
			if ((size_t)sortValueIndex >= pendChain.size())
			{
				sortValueIndex = elemSize - 1;
				actualPendIndex = 0;
			}
				auto iter = partial_lower_bound(mainChain.begin(), mainChain.end(), pendChain[sortValueIndex], elemSize);
		 		mainChain.insert(iter, pendChain.begin() + actualPendIndex, pendChain.begin() + actualPendIndex + elemSize);
		 		for (size_t i = 0; i < elemSize; i++)
					processed[actualPendIndex + i] = true;
		 	
		insertionCount--;
		currIndex--;
		}
		prevJacobsthal = currJacobsthal;
		jacobsthalN++;
		currJacobsthal = jacobsthalNumber(jacobsthalN);
	}
	// now we have to account for extra insertions if required (if we have complete elements left after
	// doing jacobsthal insertions)
	while (countUnprocessed(processed) >= elemSize)
	{
		int firstUnprocessedIndex {0};
		for (size_t i = 0; i < processed.size(); i++)
		{
			if (!processed[i])
			{
				firstUnprocessedIndex = i;
				break ;
			}
		}
		int sortableIndex = firstUnprocessedIndex + elemSize - 1;
		auto iter = partial_lower_bound(mainChain.begin(), mainChain.end(), pendChain[sortableIndex], elemSize);
		mainChain.insert(iter, pendChain.begin() + firstUnprocessedIndex, pendChain.begin() + firstUnprocessedIndex + elemSize);
		for (size_t i = 0; i < elemSize; i++)
			processed[firstUnprocessedIndex + i] = true;
	}
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		dequeSorted[i] = mainChain[i];
	}
}

void PmergeMe::dequeSort(unsigned int elemSize)
{
	auto iter = dequeSorted.begin();
	unsigned int k;
	unsigned int offset;
	for (unsigned int i = 0; i * elemSize < dequeSorted.size(); i += 2)
	{
		k = i * elemSize;
		offset = elemSize - 1;
		if (k + elemSize + offset < dequeSorted.size())
		{ 
			if(dequeSorted[k + offset] > dequeSorted[k + elemSize + offset])
			{
				std::swap_ranges(iter + k, iter + k + elemSize, iter + k + elemSize);
			}
		}
	}
	if (elemSize * 2 <= dequeSorted.size())
		dequeSort(elemSize * 2);
	if (elemSize > 1)
	{
		if (dequeSorted.size() / elemSize > 2)
		{
		std::deque<int> mainChain(dequeSorted.begin(), dequeSorted.begin() + elemSize * 2);
		std::deque<int> pendChain;
		if ((dequeSorted.size() / elemSize) % 2 == 0)
		{ 
			for (unsigned int n = 3; (n + 2) * elemSize < dequeSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					mainChain.push_back(dequeSorted[n * elemSize + i]);
				}
			}
			for (unsigned int n = 2; (n + 1) * elemSize < dequeSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(dequeSorted[n * elemSize + i]);
				}
			}
			unsigned int n = (dequeSorted.size() / elemSize) - 1;
			if ((n + 1) * elemSize < dequeSorted.size())
			{	
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(dequeSorted[n * elemSize + i]);
				}
			}
		}
		else
		{
			for (unsigned int n = 3; (n + 1) * elemSize < dequeSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					mainChain.push_back(dequeSorted[n * elemSize + i]);
				}
			}
			for (unsigned int n = 2; (n) * elemSize < dequeSorted.size(); n += 2)
			{
				for (unsigned int i = 0; i < elemSize; i++)
				{
					pendChain.push_back(dequeSorted[n * elemSize + i]);
				}
			}
		}
		dequeMultiInsert(mainChain, pendChain, elemSize);
		}
	}
	else
	{
		std::deque<int> mainChain;
		mainChain.push_back(dequeSorted[0]);
		std::deque<int> pendChain;
		if ((dequeSorted.size() / elemSize) % 2 == 0)
		{
			for (unsigned int i = 1; i < dequeSorted.size() - 2; i += 2)
				mainChain.push_back(dequeSorted[i]);
			for (unsigned int i = 2; i < dequeSorted.size(); i += 2)
				pendChain.push_back(dequeSorted[i]);
			pendChain.push_back(dequeSorted[dequeSorted.size() - 1]);
		}
		else
		{
			for (unsigned int i = 1; i < dequeSorted.size(); i += 2)
				mainChain.push_back(dequeSorted[i]);
			for (unsigned int i = 2; i < dequeSorted.size(); i += 2)
				pendChain.push_back(dequeSorted[i]);
		}
		dequeMultiInsert(mainChain, pendChain, elemSize);
	}
}

unsigned int PmergeMe::dequeJacobsthalNumber(unsigned int n)
{
	// starts with 0 and 1, then we add the previous number plus double the number before that
	// and we skip the first two to match the book referenced in the subject
	if (n == 0)
		return 1;
	std::deque<unsigned int> jacobsthalNums(n + 1);
	jacobsthalNums[0] = 1;
	jacobsthalNums[1] = 3;
	for (unsigned int i = 2; i <= n; i++)
	{
		jacobsthalNums[i] = jacobsthalNums[i-1] + (2 * jacobsthalNums[i - 2]);
	}
	return jacobsthalNums[n];
}

PmergeMe::PmergeMe(char **argv, int argc) :  _argc(argc), rawArgs((const char**)argv)
{
	if (!validateArgs())
	{
		exit(EXIT_FAILURE);
	}
	vecSorted = vecUnsorted;
	std::cout << "Unsorted vector: ";  
	for (unsigned int i = 0; i < vecUnsorted.size(); i++)
		std::cout << vecUnsorted[i] << " ";
	std::cout << std::endl;
	vecSort(1);
	std::cout << "Sorted vector: ";  
	for (unsigned int i = 0; i < vecUnsorted.size(); i++)
		std::cout << vecSorted[i] << " ";
	std::cout << std::endl;
	dequeSorted = dequeUnsorted;
	std::cout << "Unsorted deque: ";
	for (size_t i = 0; i < dequeUnsorted.size(); i++)
		std::cout << dequeUnsorted[i] << " ";
	std::cout << std::endl;
	dequeSort(1);
	std::cout << "Sorted deque: ";
	for (size_t i = 0; i < dequeSorted.size(); i++)
		std::cout << dequeSorted[i] << " ";
	std::cout << std::endl;
}

PmergeMe::~PmergeMe()
{
}
