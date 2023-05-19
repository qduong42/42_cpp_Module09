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

int binarySearch(const std::vector<int> &a, const int &item, const int low, const int high)
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

PmergeMe::PmergeMe(const int argc, char **argv): _straggler(-1)
{
	/**
	 * @brief prints before and after, before time is started
	 * 
	 */
	{
		std::string check;
		const std::string valid = "0123456789";
		long long int int_check;
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
			int_check = atoll(argv[i]);
			if (int_check > INT_MAX)
				throw std::invalid_argument("Error: Inputs are more than max int");
			numbers.push_back(atoi(argv[i]));
		}
		if (std::is_sorted(numbers.begin(), numbers.end()))
			throw PmergeMe::isSortedException();
		std::cout << "Before: ";
		if (numbers.size() <= 5)
		{
			for (size_t i = 0; i < numbers.size(); i++)
				std::cout << numbers[i] << " ";
			std::cout << std::endl;
		}
		else
		{
			for (int i = 0; i < 4;i++)
				std::cout << numbers[i] << " ";
			std::cout << "[...]" << std::endl;
		}
		std::cout << "After: ";
		std::sort(numbers.begin(), numbers.end());
		if (numbers.size() <= 5)
		{
			for (size_t i = 0; i < numbers.size(); i++)
				std::cout << numbers[i] << " ";
			std::cout << std::endl;
		}
		else
		{
			for (int i = 0; i < 4;i++)
				std::cout << numbers[i] << " ";
			std::cout << "[...]" << std::endl;
		}
	}
	double startTime = getProcessorTime();

	// check for only digits in argv, and push all back to int vector
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
		numbers.push_back(this->_straggler);
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
	double endTime = getProcessorTime();

    // Calculate the difference in time
    double timeDifference = endTime - startTime;

    // Output the time difference
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " <<  timeDifference << " us" << std::endl;
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

const char*	PmergeMe::isSortedException::what() const throw()
{
	return ("Error: Already Sorted");
}

int PmergeMe::getStraggler()const
{
	return (this->_straggler);
}

