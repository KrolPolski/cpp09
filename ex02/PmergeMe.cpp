/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:31 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/05 13:20:33 by rboudwin         ###   ########.fr       */
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

void PmergeMe::complexMultiInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize)
{
	//std::cout << "Hello from complexMultiInsert for elemSize: " << elemSize << std::endl;
	//std::cout << "Main chain: ";
	//for (unsigned int i = 0; i < mainChain.size(); i++)
	//	std::cout << mainChain[i] << " ";
	//std::cout << std::endl;
	//std::cout << "pendChain: ";
	// for (unsigned int i = 0; i < pendChain.size(); i++)
	// 	std::cout << pendChain[i] << " ";
	// std::cout << std::endl;
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
		 	// 	std::cout << "SortValueIndex: " << sortValueIndex << " Value: " << pendChain[sortValueIndex] << " we believe this should be inserted before ";
			// 	if (iter != mainChain.end())
			// 		std::cout << *iter << std::endl;
			// 	else
			// 		std::cout << "the end" << std::endl;
			
		 	// 	std::cout << "Attempting insertion of pendChain" << std::endl;
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
		// std::cout << "We have this many numbers unprocessed: " << countUnprocessed(processed) << std::endl;
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
		//std::cout << "SortableIndex: " << sortableIndex << " Value: " << pendChain[sortableIndex] << " we believe this should be inserted before ";
		// if (iter != mainChain.end())
		// 		std::cout << *iter << std::endl;
		// else
		// 	std::cout << "the end" << std::endl;
		// std::cout << "Attempting insertion of pendChain" << std::endl;
		mainChain.insert(iter, pendChain.begin() + firstUnprocessedIndex, pendChain.begin() + firstUnprocessedIndex + elemSize);
		for (size_t i = 0; i < elemSize; i++)
			processed[firstUnprocessedIndex + i] = true;
	}
	//std::cout << "All done, vecSorted now: ";
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		vecSorted[i] = mainChain[i];
		//std::cout << vecSorted[i] << " ";
	}
	if (mainChain.size() < vecSorted.size())
	{
		//std::cout << "Remaining non-participants: ";
		//for (size_t i = mainChain.size(); i < vecSorted.size(); i++)
			//std::cout << vecSorted[i] << " ";
	}
	//std::cout << std::endl;
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
			//vecComparisons++;
		}
	}
	// std::cout << "iteration: ";
	// for (unsigned int l = 0; l < vecSorted.size(); l++)
	// 	std::cout << vecSorted[l] << " ";
	// std::cout << std::endl;
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
			//std::cout << "We've decided we have an even number of participating elements" << std::endl;
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
			//std::cout << "Going to attempt to insert n: " << n << " to the pend Chain" << std::endl;
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
			//std::cout << "We've decided we have an odd number of participating elements" << std::endl;
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
		//std::cout << "For element size: " << elemSize << " the main chain is: " << std::endl;
		// for (unsigned int i = 0; i < mainChain.size(); i++)
		// 	std::cout << mainChain[i] << " ";
		// std::cout << std::endl;
		// std::cout << "pendChain is: ";
		// for (unsigned int i= 0; i < pendChain.size(); i++)
		// 	std::cout << pendChain[i] << " ";
		// std::cout << std::endl;
		complexMultiInsert(mainChain, pendChain, elemSize);
		}
	}
	else
	{
		std::vector<int> mainChain;
		mainChain.push_back(vecSorted[0]);
		std::vector<int> pendChain;
		if ((vecSorted.size() / elemSize) % 2 == 0)
		{
			//std::cout << "We decided we have an even number of elements" << std::endl;
			for (unsigned int i = 1; i < vecSorted.size() - 2; i += 2)
				mainChain.push_back(vecSorted[i]);
			for (unsigned int i = 2; i < vecSorted.size(); i += 2)
				pendChain.push_back(vecSorted[i]);
			pendChain.push_back(vecSorted[vecSorted.size() - 1]);
		}
		else
		{
			//std::cout << "We decided we have an odd number of elements" << std::endl;
			for (unsigned int i = 1; i < vecSorted.size(); i += 2)
				mainChain.push_back(vecSorted[i]);
			for (unsigned int i = 2; i < vecSorted.size(); i += 2)
				pendChain.push_back(vecSorted[i]);
		}
		complexMultiInsert(mainChain, pendChain, elemSize);
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
		std::cout << vecUnsorted[i] << " ";
	std::cout << std::endl;
	vecSort(1);
	std::cout << "Sorted vector: ";  
	for (unsigned int i = 0; i < vecUnsorted.size(); i++)
		std::cout << vecSorted[i] << " ";
	std::cout << std::endl;
}

PmergeMe::~PmergeMe()
{
}
