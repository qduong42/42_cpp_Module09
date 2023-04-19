#include "../include/BitcoinExchange.hpp"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

bool	validDateFormat(std::string str)
{
	if (str.length() != 10)
		return (false);
	for (size_t i = 0; i < str.length(); ++i)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (false);
	}
	return (true);
}

bool	checkDate(std::string str)
{
	std::cout << "CheckDate buffer:" << str << "END" << std::endl;
	size_t end = str.find_last_not_of(" ");
    str = (end == std::string::npos) ? "" : str.substr(0, end + 1);
	std::cout << "CheckDate buffer:" << str << "END" << std::endl;
	if (!validDateFormat(str))
		return (false);
	int year = std::atoi(str.substr(0, 4).c_str());
	std::cout << "year: " << year << std::endl;
	int	month = std::atoi(str.substr(5, 7).c_str());
	std::cout << "month: " << month << std::endl;
	int	day = std::atoi(str.substr(8, 10).c_str());
	std::cout << "day: " << day << std::endl;
	if (month > 12 || day > 31 || month == 0 || day == 0)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		if (day > 29)
			return false;
		if (year % 4 != 0 && (year % 100 == 0 || year % 400 != 0) && day == 29)
			return false;
	}
	return (true);
}

bool checkValue(std::string value)
{
	std::cout << "CheckValue buffer:" << value << "END" << std::endl;
	size_t start = value.find_first_not_of(" ");
    value = (start == std::string::npos) ? "" : value.substr(start);
	std::cout << "CheckValue buffer:" << value << "END" << std::endl;
	char *endptr;
	float conv;
	conv = strtod(value.c_str(), &endptr);
	if (endptr == value.c_str() || *endptr != '\0') 
	{
		return (false);
    }
	if (conv < 0 || conv > 1000)
	{
        return (false);
    } 
	return (true);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::fstream	inFile(argv[1]);
		if (inFile.fail())
		{
			std::cerr << "Error. could not open input file." << std::endl;
			return (EXIT_FAILURE);
		}
		std::string		dataFileName("data.csv");
		std::fstream	dataFile(dataFileName.c_str());

		if (dataFile.fail())
		{
			std::cerr << "Error. could not open database file (data.csv). Make sure data.csv is in same folder as btc" << std::endl;
			return (EXIT_FAILURE);
		}
		// std::string buffer;
		// std::getline(inFile, buffer);
		// while (buffer.length() != 0)
		// {
		// std::getline(inFile, buffer);
		// std::cout << buffer << std::endl;
		// }
		std::string	buffer;
		while (getline(inFile, buffer))
		{
			std::cout << "\n";
			// std::cout << buffer << std::endl;
			// size_t i = 0;
			// i = buffer.find("|");
			if (buffer == "date | value")
			{
				continue;
			}
			size_t pipePos = buffer.find("|");
			std::cout << "pipePos: " << pipePos << std::endl;
			if (pipePos == std::string::npos || pipePos == buffer.size() - 1)
			{
				std::cerr << "Error: invalid input line." << std::endl;
				continue;
			}
			if (checkDate(buffer.substr(0, pipePos)) == false)
			{
				std::cerr << "Error. Invalid date" << std::endl;
			}
			if (checkValue(buffer.substr(pipePos + 1)) == false)
			{
				std::cerr << "Error. Invalid value" << std::endl;
			}
			// std:: cout << i << std::endl;
			// std::cout << buffer.size() - 1 << std::endl;
		}
		inFile.close();
	}
	else
	{
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
