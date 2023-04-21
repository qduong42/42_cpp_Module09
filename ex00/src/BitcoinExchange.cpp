#include "../include/BitcoinExchange.hpp"

#include <iterator>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

//	CONSTRUCTORS | DESTRUCTOR

BitcoinExchange::BitcoinExchange():
	_exchange(std::map<std::string, float>())
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & other):
	_exchange(other._exchange)
{
	
}

BitcoinExchange::BitcoinExchange(std::map<std::string, float> map):
	_exchange(map)
{

}

BitcoinExchange &	BitcoinExchange::operator=(const BitcoinExchange & other)
{
	if (this != &other)
	{
		new (this) BitcoinExchange(other);
	}
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::string dataFileName):
	_exchange(std::map<std::string, float>())
{
	std::map<std::string, float>	data;
	std::fstream					dataFile(dataFileName.c_str());

	if (dataFile.fail())
		throw	invalidFileException();

	std::string	buffer;
	while (getline(dataFile, buffer))
	{
		if (buffer == "date,exchange_rate")
			continue;
		
		std::size_t	commaPos = buffer.find(',');
		std::string	dateStr(buffer.substr(0, commaPos));
		std::string	priceStr(buffer.substr(commaPos + 1, buffer.length()));
		std::pair<std::string, float>	pair;
		pair = make_pair(dateStr, atof(priceStr.c_str()));
		data.insert(pair);
	}
	dataFile.close();
	new (this) BitcoinExchange(data);
	// for(std::map<std::string, float>::const_iterator it = this->_exchange.begin();
	// 	it != this->_exchange.end(); ++it)
	// {
	// 	std::cout << it->first << " " << it->second << "\n";
	// }
}

BitcoinExchange::~BitcoinExchange()
{}

const char*	BitcoinExchange::invalidFileException::what() const throw()
{
	return ("Error: BitcoinExchange: invalid data file.");
}

//	MEMBER FUNCTIONS

