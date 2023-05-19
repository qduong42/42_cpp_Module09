#include "../include/BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

bool	validDateFormat(std::string str)
{
	if (str.length() != 10)
		return (true);
	for (size_t i = 0; i < str.length(); ++i)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (true);
	}
	return (false);
}

bool	checkDate(std::string str)
{
	size_t end = str.find_last_not_of(" ");
    str = (end == std::string::npos) ? "" : str.substr(0, end + 1);
	if (validDateFormat(str))
		return (true);
	int year = std::atoi(str.substr(0, 4).c_str());
	int	month = std::atoi(str.substr(5, 7).c_str());
	int	day = std::atoi(str.substr(8, 10).c_str());
	if (month > 12 || day > 31 || month == 0 || day == 0)
		return (true);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return true;
	if (month == 2)
	{
		if (day > 29)
			return true;
		if (year % 4 != 0 && (year % 100 == 0 || year % 400 != 0) && day == 29)
			return true;
	}
	return (false);
}

std::string parseDate(std::string str)
{
	size_t end = str.find_last_not_of(" ");
    str = (end == std::string::npos) ? "" : str.substr(0, end + 1);
	return str;
}


bool	checkValue(std::string value)
{
	size_t start = value.find_first_not_of(" ");
    value = (start == std::string::npos) ? "" : value.substr(start);
	char *endptr;
	float conv;
	conv = strtod(value.c_str(), &endptr);
	if (endptr == value.c_str() || *endptr != '\0') 
	{
		return (true);
    }
	if (conv < 0 || conv > 1000)
	{
        return (true);
    } 
	return (false);
}

float parseValue(std::string value)
{
	size_t start = value.find_first_not_of(" ");
	value = (start == std::string::npos) ? "" : value.substr(start);
	
	float conv;
	conv = atof(value.c_str());
	return conv;
}

int checkInputFirstLine(std::fstream& f)
{
	std::string	buffer;
	getline(f, buffer);
	if (buffer != "date | value")
	{
		std::cerr << "Error. Invalid input, first line needs to be:date | value" << std::endl;
		f.close();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool lastcharPipe(size_t& pipepos, std::string& buffer)
{
	if (pipepos == buffer.size() - 1)
		return (true);
	else
		return (false);
}

bool noPipe(size_t& pipepos)
{
	if (pipepos == std::string::npos)
		return true;
	else
		return false;
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
		BitcoinExchange Exchange;
		try
		{
			BitcoinExchange ExchangeTry(dataFileName);
			Exchange = ExchangeTry;
		}
		catch (std::exception&e)
		{
			std::cerr << "Error: can not open dataFile." << std::endl;
			std::cerr << e.what() << std::endl;
		}
		if (checkInputFirstLine(inFile) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		std::string	buffer;
		while (getline(inFile, buffer))
		{
			size_t pipePos = buffer.find("|");
			if (noPipe(pipePos) || lastcharPipe(pipePos, buffer))
			{
				std::cerr << "Error: invalid input line." << std::endl;
				continue;
			}
			if (checkDate(buffer.substr(0, pipePos)))
			{
				std::cerr << "Error. Invalid date" << std::endl;
				continue;
			}
			if (checkValue(buffer.substr(pipePos + 1)))
			{
				std::cerr << "Error. Invalid value" << std::endl;
				continue;
			}
			std::string date;
			date = parseDate(buffer.substr(0, pipePos));
			float value;
			value = parseValue(buffer.substr(pipePos + 1));
			float exchange_rate;
			try
			{
				exchange_rate = Exchange.find(buffer.substr(0, pipePos));
				Exchange.print(exchange_rate, value, date);
			}
			catch (std::exception&e) 
			{
				std::cerr << e.what() << std::endl;
			}
		}
		inFile.close();
	}
	else
	{
		std::cerr << "Error: Invalid Number of arguments." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
