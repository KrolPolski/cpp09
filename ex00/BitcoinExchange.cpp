/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:26 by rboudwin          #+#    #+#             */
/*   Updated: 2025/02/26 14:24:42 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string inputFileName)
{	
	_inputFileName = inputFileName;
	_inputFile.open(inputFileName, std::fstream::in);
	if (!_inputFile.is_open())
		throw std::ios_base::failure("Failed to open input file");
	_dataFile.open("data.csv", std::fstream::in);
	if (!_dataFile.is_open())
		throw std::ios_base::failure("Failed to open data.csv");
	populateExchangeRates();
	populateInputData();
}

BitcoinExchange::~BitcoinExchange()
{	
}

void BitcoinExchange::populateExchangeRates()
{
	std::string currLine;
	std::string date;
	float		value;
	
	size_t delimiter;
	while (std::getline(_dataFile, currLine))
	{
		delimiter = currLine.find(',');
		if (delimiter == currLine.npos)
			std::cout << "No delimiter found" << std::endl;
		else
		{
			date = currLine.substr(0, delimiter);
			if (date == "date")
				continue ;
			//std::cout << date << std::endl;
			value = stof(currLine.substr(delimiter + 1));
			//std::cout << currLine.substr(delimiter + 1) << " becomes " << value << std::endl;
			_exchangeRates.insert({date, value});
		}
	}
	/*std::cout << std::endl << "Now displaying map: " << std::endl;
	for (const auto& pair : _exchangeRates)
	{
		std::cout << pair.first << ": " << pair.second << std::endl;
	}*/
}

bool BitcoinExchange::isValidDateFormat(const std::string& date) 
{
    std::regex datePattern(R"(^(19|20)\d\d-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    return std::regex_match(date, datePattern);
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	unsigned int year = std::stoi(date.substr(0, 4));
    unsigned int month = std::stoi(date.substr(5, 2));
    unsigned int day = std::stoi(date.substr(8, 2));
	if (year < 2009)
		return false;
	if (month > 12)
		return false;
	if (day > 31)
		return false;
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return false;
	}
	if (month == 2)
	{
		if (year % 4 == 0)
		{
			if (day > 29)
				return false;
		}
		else
		{
			if (day > 28)
				return false;
		}
	}
	return true;
}

void BitcoinExchange::populateInputData()
{
	std::string currLine;
	std::string date;
	float		value;
	
	size_t delimiter;
	while (std::getline(_inputFile, currLine))
	{
		delimiter = currLine.find('|');
		if (delimiter == currLine.npos)
			std::cout << "No delimiter found" << std::endl;
		else
		{
			date = currLine.substr(0, delimiter);
			date.erase(date.find_last_not_of(" ") + 1);
			if (date == "date")
				continue ;
				
			value = stof(currLine.substr(delimiter + 1));
			// garbage values?
			std::cout << date << " | " << value << std::endl;
			if (isValidDateFormat(date) && isValidDate(date))
				_inputData.insert({date, value});
			else
				std::cerr << "Invalid date: " << date << std::endl;
		}
	}
}