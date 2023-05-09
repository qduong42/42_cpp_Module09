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
	}
	dataFile.close();
	new (this) BitcoinExchange(data);
	// for(std::map<std::string, float>::const_iterator it = this->_exchange.begin();
	// 	it != this->_exchange.end(); ++it)
	// {
	// 	std::cout << it->first << " " << it->second << "\n";
	// }
}

float BitcoinExchange::find(std::string date)
{
	size_t end = date.find_last_not_of(" ");
    date = (end == std::string::npos) ? "" : date.substr(0, end + 1);
	if (date < this->_exchange.begin()->first)
	{
		throw	precedeException();
	}
	if (date > this->_exchange.end()->first)
	{
		throw exceedException();
	}
	std::map<std::string, float>::iterator it;
	it = this->_exchange.find(date);
	return 1;
}

BitcoinExchange::~BitcoinExchange()
{}

const char*	BitcoinExchange::invalidFileException::what() const throw()
{
	return ("Error: BitcoinExchange: invalid data file.");
}

const char*	BitcoinExchange::precedeException::what() const throw()
{
	return ("Error: Date preceeds exchange data");
}

const char*	BitcoinExchange::exceedException::what() const throw()
{
	return ("Error: Date exceeds exchange data");
}
//	MEMBER FUNCTIONS

