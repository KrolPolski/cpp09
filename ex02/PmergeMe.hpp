/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:35:39 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/31 14:00:08 by rboudwin         ###   ########.fr       */
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
	//void sortPairsInPlace();
	void vecSort(unsigned int elem_size);
	unsigned int jacobsthalNumber(unsigned int n);
	int binarySearchNthElement(const std::vector<int> mainChain, int target, int elemSize);
	void binaryInsert(std::vector<int> mainChain, std::vector<int> pendChain, unsigned int elemSize, int nonParticipants);
public:
	PmergeMe() = delete;
	PmergeMe(char **argv, int argc);
	PmergeMe(const PmergeMe& other) = delete;
	PmergeMe& operator=(const PmergeMe& other) = delete;
	~PmergeMe();
};
