#include "../include/PmergeMe.hpp"

//	CONSTRUCTORS | DESTRUCTOR

PmergeMe::PmergeMe() :_straggler(-1)
{}

//custom mycomparison function to sort by second
bool PmergeMe::myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
	return (a.second < b.second);
}

//in microseconds
double getProcessorTime()
{
    std::clock_t currentTime = std::clock();
    double processorTime = static_cast<double>(currentTime) / CLOCKS_PER_SEC * 1000000;
    return processorTime;
}

int binarySearch(std::vector<int> &a, int item, int low, int high)
{
	//if the search range has been narrowed down to a single element or has become invalid (high < low).
    if (high <= low) 
	{
        if (item > a[low])
            return low + 1;
        else
            return low;
    }
    int mid = (low + high) / 2;
    if (item == a[mid])
        return mid + 1;
    else if (item > a[mid])
        return binarySearch(a, item, mid + 1, high);
    else
        return binarySearch(a, item, low, mid - 1);
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
	double startTime = getProcessorTime();
	/**
	 * @brief check for only digits in argv
	 * 
	 */
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
	/**
	 * @brief if size cant be divided by 2 without remainder = straggler present assigned straggler value and pop.
	 * 
	 */
	if(numbers.size() % 2 != 0)
	{
		this->_straggler = numbers.back();
		numbers.pop_back();
	}
	// for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	/**
	 * @brief assign vecpairs to first and second
	 * 
	 */
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
		/**
		 * @brief swap vecpairs to order them
		 * 
		 * @param it iterates through vecpairs
		 */
		for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		{
			if (it->first > it->second)
			{
				std::swap(it->first, it->second);
			}
		}
		// std::cout << "=========Paired =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		// Sorts vecPairs
		sort(vecPairs.begin(), vecPairs.end(), myComparison);
		// std::cout << "=========Sorted by second =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		//insert straggler at end
		if (this->_straggler > -1)
		{
			vecPairs.push_back(std::make_pair(this->_straggler, -1));
		}
		// std::cout << "=========With straggler =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		//add straggler to vecPairs
		// put vecPairs second into main chain
		std::vector <int> main_chain;
		for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
		{
			if (it->second > -1)
				main_chain.push_back(it->second);
		}
		// std::cout << "========= Main_Chain =======" << std::endl;
		// for (std::vector<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
		// {
		// 		std::cout << *it << std::endl;
		// }
		//generate Jacobsthal up to x
		std::vector<int> jacobsthal;
		PmergeMe::make_jacobs_sequence(vecPairs, jacobsthal);
		for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); it++)
		{
			*it = *it -1;
		}
		for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); it++)
		{
			if (*it < static_cast<int>(vecPairs.size() - 1))
			{
				int insert_pos;
				insert_pos = binarySearch(main_chain, vecPairs.at(*it).first, 0, main_chain.size() - 1);
				// std::cout << "insert+pos" << insert_pos << std::endl;
				main_chain.insert(main_chain.begin() + insert_pos, vecPairs.at(*it).first);
			}
		}
		// 		std::cout << "========= Main_Chain AFTER insert (jacob) =======" << std::endl;
		// for (std::vector<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
		// {
		// 		std::cout << *it << std::endl;
		// }
	}
	double endTime = getProcessorTime();

    // Calculate the difference in time
    double timeDifference = endTime - startTime;

    // Output the time difference
    std::cout << "BINARY SEARCH Time difference: " << timeDifference << " microseconds" << std::endl;
		double sTime = getProcessorTime();
	/**
	 * @brief check for only digits in argv
	 * 
	 */
	std::string check2;
	std::string valid2 = "0123456789";
	std::vector<int> numbers2;
	for (int i = 1; i < argc; i++)
	{
		check2 = argv[i];
		// std::cout << check << std::endl;
		for (std::string::iterator it = check2.begin(); it!= check2.end(); it++)
		{
			if (valid2.find(*it) == std::string::npos)
				throw PmergeMe::invalidNumberException();
		}
		numbers2.push_back(atoi(argv[i]));
	}
	/**
	 * @brief if size cant be divided by 2 without remainder = straggler present assigned straggler value and pop.
	 * 
	 */
	if(numbers2.size() % 2 != 0)
	{
		this->_straggler2 = numbers2.back();
		numbers2.pop_back();
	}
	// for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	/**
	 * @brief assign vecpairs to first and second
	 * 
	 */
	std::vector<std::pair<int, int > > vecPairs2;
	if (numbers2.size() >= 2)
	{
		std::vector<int>::iterator it_next = numbers2.begin();
		std::vector<int>::iterator it_current = it_next++;
		for (int times = numbers2.size() / 2; times > 0; times--)
		{
			std::pair <int, int> pair;
			pair = std::make_pair(*it_current, *it_next);
			vecPairs2.push_back(pair);
			std::advance(it_current, 2);
			std::advance(it_next, 2);
		}
		/**
		 * @brief swap vecpairs to order them
		 * 
		 * @param it iterates through vecpairs
		 */
		for (std::vector<std::pair<int, int > >::iterator it = vecPairs2.begin(); it != vecPairs2.end(); it++)
		{
			if (it->first > it->second)
			{
				std::swap(it->first, it->second);
			}
		}
		// std::cout << "=========Paired =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs2.begin(); it != vecPairs2.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		// Sorts vecPairs
		sort(vecPairs2.begin(), vecPairs2.end(), myComparison);
		// std::cout << "=========Sorted by second =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs2.begin(); it != vecPairs2.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		//insert straggler at end
		if (this->_straggler2 > -1)
		{
			vecPairs2.push_back(std::make_pair(this->_straggler2, -1));
		}
		// std::cout << "=========With straggler =======" << std::endl;
		// for (std::vector<std::pair<int, int > >::iterator it = vecPairs2.begin(); it != vecPairs2.end(); it++)
		// {
		// 		std::cout << it->first << "," << it->second << std::endl;
		// }
		//add straggler to vecPairs
		// put vecPairs second into main chain
		std::vector <int> main_chain2;
		for (std::vector<std::pair<int, int > >::iterator it = vecPairs2.begin(); it != vecPairs2.end(); it++)
		{
			if (it->second > -1)
				main_chain2.push_back(it->second);
		}
		// std::cout << "========= Main_Chain =======" << std::endl;
		// for (std::vector<int>::iterator it = main_chain2.begin(); it != main_chain2.end(); it++)
		// {
		// 		std::cout << *it << std::endl;
		// }
		//generate Jacobsthal up to x
		std::vector<int> jacobsthal2;
		PmergeMe::make_jacobs_sequence(vecPairs2, jacobsthal2);
		for (std::vector<int>::iterator it = jacobsthal2.begin(); it != jacobsthal2.end(); it++)
		{
			*it = *it -1;
		}
		for (std::vector<int>::iterator it = jacobsthal2.begin(); it != jacobsthal2.end(); it++)
		{
			if (*it < static_cast<int>(vecPairs2.size() - 1))
			{
				std::vector<int>::iterator insertPos = main_chain2.begin();
				while (insertPos != main_chain2.end() && *insertPos < vecPairs2.at(*it).first)
				{
					++insertPos;
				}

			// Insert the element at the found position
			main_chain2.insert(insertPos, vecPairs2.at(*it).first);
				// int insert_pos;
				// insert_pos = binarySearch(main_chain, vecPairs2.at(*it).first, 0, main_chain2.size() - 1);
				// std::cout << "insert+pos" << insert_pos << std::endl;
				// main_chain2.insert(main_chain2.begin() + insert_pos, vecPairs2.at(*it).first);

			}
		}
		// 		std::cout << "========= Main_Chain AFTER insert (jacob) =======" << std::endl;
		// for (std::vector<int>::iterator it = main_chain2.begin(); it != main_chain2.end(); it++)
		// {
		// 		std::cout << *it << std::endl;
		// }
	}
	double eTime = getProcessorTime();

    // Calculate the difference in time
    double tDifference = eTime - sTime;
	std::cout << "LINEAR SEARCH Time difference: " << tDifference << std::endl;
}



int	jacobsthalNumber(int idx)
{
	if (idx == 0)
		return (0);
	if (idx == 1)
		return (1);
	int	jacobsthal;
	jacobsthal = jacobsthalNumber(idx - 1) + 2 * jacobsthalNumber(idx - 2);
	return (jacobsthal);
}

void PmergeMe::make_jacobs_sequence(std::vector<std::pair<int, int > >& paired_vectr, std::vector<int>& jacobs_num)
{
    int i = 3;
    jacobs_num.push_back(1);

    while(std::find(jacobs_num.begin(), jacobs_num.end(), paired_vectr.size()) == jacobs_num.end())
	{
        int num = jacobsthalNumber(i++);
        jacobs_num.push_back(num);
        while (std::find(jacobs_num.begin(), jacobs_num.end(), --num) == jacobs_num.end())
        {
            jacobs_num.push_back(num);
        }
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
