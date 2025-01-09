/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:34 by rboudwin          #+#    #+#             */
/*   Updated: 2025/01/09 12:10:43 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
int main(int argc, char **argv)
{
	if (argc != 2)
	{	
		std::cerr << "Please provide one data file as an argument: ./btc <filename>" << std::endl;
		return(EXIT_FAILURE);
	}
	std::string inputFileName {argv[1]};
	try
	{
		BitcoinExchange btc(inputFileName);
		btc.populateExchangeRates();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}