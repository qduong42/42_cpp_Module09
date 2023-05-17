#include "../include/PmergeMe.hpp"

//	CONSTRUCTORS | DESTRUCTOR

PmergeMe::PmergeMe()
{}

bool PmergeMe::myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
	return (a.second < b.second);
}

PmergeMe::PmergeMe(int argc, char **argv): _straggler(-1)
{
	// struct s_myComparison
	// {
	// 	bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b)const
	// 	{
	// 	return (a.second < b.second);
	// 	}
	// }myComparison;
	std::string check;
	std::string valid = "0123456789";
	std::vector<int> numbers;
	for (int i = 1; i < argc; i++)
	{
		check = argv[i];
		// std::cout << check << std::endl;
		for (std::string::iterator it = check.begin(); it!= check.end(); it++)
		{
			if (valid.find(*it) == std::string::npos)
				throw PmergeMe::invalidNumberException();
		}
		numbers.push_back(atoi(argv[i]));
	}
	if(numbers.size() % 2 != 0)
	{
		this->_straggler = numbers.back();
		numbers.pop_back();
	}
	// for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	std::vector<std::pair<int, int > > vecPairs;
	if (numbers.size() >= 2)
	{
		std::vector<int>::iterator it_next = numbers.begin();
		std::vector<int>::iterator it_current = it_next++;
		for (int times = numbers.size() / 2; times > 0; times--)
		{
			std::pair <int, int> pair;
			pair = std::make_pair(*it_current, *it_next);
			vecPairs.push_back(pair);
			std::advance(it_current, 2);
			std::advance(it_next, 2);
		}
		for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		{
			if (it->first > it->second)
			{
				std::swap(it->first, it->second);
			}
		}
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		sort(vecPairs.begin(), vecPairs.end(), myComparison);
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
	}
}

PmergeMe::PmergeMe(PmergeMe const& obj): _straggler(obj._straggler)
{
}

PmergeMe& PmergeMe::operator=(PmergeMe const& obj)
{
	if (this != &obj)
	{
		this->_straggler = obj.getStraggler();
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{}

//	MEMBER FUNCTIONS

const char*	PmergeMe::invalidNumberException::what() const throw()
{
	return ("Error: Invalid Number. Only positive digits are allowed, without spaces.");
}

int PmergeMe::getStraggler()const
{
	return (this->_straggler);
}
