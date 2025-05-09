/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:39 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/05 14:44:33 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <chrono>
#include <iostream>

class PmergeMe
{
	private:
		std::vector<int> vecUnsorted;
		std::deque<int>	dequeUnsorted;
		std::vector<int> vecSorted;
		std::deque<int> dequeSorted;
		int _argc;
		const char **rawArgs;
		bool validateArgs();
		void vecSort(unsigned int elemSize);
		void dequeSort(unsigned int elemSize);
		unsigned int jacobsthalNumber(unsigned int n);
		unsigned int dequeJacobsthalNumber(unsigned int n);
		int binarySearchNthElement(const std::vector<int>& mainChain, int target, int elemSize);
		void vectorMultiInsert(std::vector<int>& mainChain, std::vector<int>& pendChain, unsigned int elemSize);
		void dequeMultiInsert(std::deque<int>& mainChain, std::deque<int>& pendChain, unsigned int elemSize);
		template<typename Iterator, typename T>
		Iterator partial_lower_bound(Iterator first, Iterator last, const T& value, size_t elemSize);
		unsigned int countUnprocessed(std::vector<bool>& processed);
		unsigned int countUnprocessed(std::deque<bool>& processed);
	public:
		PmergeMe() = delete;
		PmergeMe(char **argv, int argc);
		PmergeMe(const PmergeMe& other) = delete;
		PmergeMe& operator=(const PmergeMe& other) = delete;
		~PmergeMe();
};

/* Uses binary search on partially sorted container, only checking based on elemSize-th elements */
template<typename Iterator, typename T>
Iterator PmergeMe::partial_lower_bound(Iterator first, Iterator last, const T& value, size_t elemSize) 
{
    typename std::iterator_traits<Iterator>::difference_type count = (last - first) / elemSize;
    
    if (count <= 0)
        return first;
        
    Iterator it;
    typename std::iterator_traits<Iterator>::difference_type step;
    
    while (count > 0) {
        it = first;
        step = count / 2;
        std::advance(it, step * elemSize);
        
        if (*(it + (elemSize - 1)) < value) {
            first = it + elemSize;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    
    return first;
}