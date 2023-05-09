#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

bool	validDateFormat(std::string);

bool	validDate(std::string);

class	BitcoinExchange
{
	private:
		std::map<std::string, float>	_exchange;
	
	public:
		BitcoinExchange();
		BitcoinExchange(std::map<std::string, float>);
		BitcoinExchange(const BitcoinExchange &);
		~BitcoinExchange();
		BitcoinExchange&	operator=(const BitcoinExchange &);


		BitcoinExchange(std::string);

		float		find(std::string);
		// std::string	firstDate();
		// std::string	lastDate();

	class	invalidFileException
	{
		const char *	what() const throw();
	};

	class	precedeException
	{
		const char *	what() const throw();
	};

	class	exceedException
	{
		const char *	what() const throw();
	};
};

#endif
