/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:39 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/05 12:50:49 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <string>

class PmergeMe
{
private:
	std::vector<int> vecUnsorted;
	std::list<int>	listUnsorted;
	std::vector<int> vecSorted;
	std::list<int> listSorted;
	int _argc;
	const char **rawArgs;
	unsigned int vecComparisons {0};
	bool validateArgs();
	void vecSort(unsigned int elemSize);
	unsigned int jacobsthalNumber(unsigned int n);
	int binarySearchNthElement(const std::vector<int>& mainChain, int target, int elemSize);
	void complexMultiInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize);
	void binaryInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize, int nonParticipants);
	template<typename Iterator, typename T>
	Iterator partial_lower_bound(Iterator first, Iterator last, const T& value, size_t elemSize);
	unsigned int countUnprocessed(std::vector<bool>& processed);
public:
	PmergeMe() = delete;
	PmergeMe(char **argv, int argc);
	PmergeMe(const PmergeMe& other) = delete;
	PmergeMe& operator=(const PmergeMe& other) = delete;
	~PmergeMe();
};
template<typename Iterator, typename T>
Iterator PmergeMe::partial_lower_bound(Iterator first, Iterator last, const T& value, size_t elemSize) 
{
    Iterator it = first;
    for (size_t i = elemSize - 1; it < last; it += elemSize) {
        if (*(it + i) >= value) {
            return it;
        }
    }
    return last;
}