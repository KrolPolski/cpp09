/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:37:39 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/07 12:11:33 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Please provide some integers to be sorted, like this: ./PmergeMe 2 1 4" << std::endl;
		return(EXIT_FAILURE);
	}
	
	PmergeMe MrMerge(argv);
}