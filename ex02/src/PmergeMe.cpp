#include "../include/PmergeMe.hpp"

//	CONSTRUCTORS | DESTRUCTOR

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

void make_jacobs_sequences(size_t t, std::vector<int>& jacobs_num)
{
    int i = 3;
    jacobs_num.push_back(1);

    while(std::find(jacobs_num.begin(), jacobs_num.end(), t) == jacobs_num.end())
	{
        int num = jacobsthalNumber(i++);
        jacobs_num.push_back(num);
        while (std::find(jacobs_num.begin(), jacobs_num.end(), --num) == jacobs_num.end())
        {
            jacobs_num.push_back(num);
        }
    }
}

PmergeMe::PmergeMe() :_straggler(-1)
{}

//custom mycomparison function to sort by second
bool PmergeMe::myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
	return (a.second < b.second);
}

//in microseconds
double PmergeMe::getProcessorTime() const
{
    std::clock_t currentTime = std::clock();
    double processorTime = static_cast<double>(currentTime) / CLOCKS_PER_SEC * SEC_TO_MS;
    return processorTime;
}

int PmergeMe::binarySearch(const std::vector<int> &a, const int &item, const int low, const int high)const
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
					throw PmergeMe::invalidInputException();
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
	std::vector<int> jacobsthal;
	make_jacobs_sequences((argc /2), jacobsthal);
	for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); it++)
		*it = *it -1;
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
				throw PmergeMe::invalidInputException();
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
	// Sorts vecPairs
	sort(vecPairs.begin(), vecPairs.end(), PmergeMe::myComparison);
	//insert straggler at end
	//add straggler to vecPairs
	if (this->_straggler > -1)
	{
		vecPairs.push_back(std::make_pair(this->_straggler, -1));
		numbers.push_back(this->_straggler);
	}
	// put vecPairs second into main chain
	std::vector <int> main_chain;
	for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
	{
		if (it->second > -1)
			main_chain.push_back(it->second);
	}
	//generate Jacobsthal up to x
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
/* 	for (std::vector<std::pair<int, int > >::iterator it = vecPairs.begin(); it != vecPairs.end() ; it++)
	{
		int insert_pos;
		insert_pos = binarySearch(main_chain, it->first, 0, main_chain.size() -1);
		main_chain.insert(main_chain.begin() + insert_pos, it->first);
	} */
	
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
{}

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

const char*	PmergeMe::invalidInputException::what() const throw()
{
	return ("Error: Invalid Input. Only positive digits are allowed, without spaces.");
}

const char*	PmergeMe::isSortedException::what() const throw()
{
	return ("Error: Already Sorted");
}

int PmergeMe::getStraggler()const
{
	return (this->_straggler);
}

