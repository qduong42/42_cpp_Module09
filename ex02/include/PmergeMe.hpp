#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
//indirectly included in vector & deque
#include <utility>
#include <algorithm>

#define SEC_TO_MS 1000000

//HELPER FUNCTIONS: Not included as class functions

int	jacobsthalNumber(int idx);

void make_jacobs_sequences(size_t t, std::vector<int>& jacobs_num);

bool myComparison(const std::pair<int, int>&a, const std::pair<int, int>&b);

template <typename A, typename B>
class PmergeMe
{
	private:

	int _straggler;
	double getProcessorTime() const;
	int binarySearch(const A&, const int&, const int, const int)const;
	void output_print(const A&, const double&)const;
	void pre_print_info(const int &, char**);

	public:

		PmergeMe();
		PmergeMe(const int&, char **);
		PmergeMe(PmergeMe const& obj);
		PmergeMe& operator=(PmergeMe const& obj);
		~PmergeMe();
		int getStraggler()const;
	class	invalidInputException : public std::exception
	{
		const char *	what() const throw();
	};
	class	isSortedException : public std::exception
	{
		const char *	what() const throw();
	};
};

template <typename A, typename B>
PmergeMe<A, B>::PmergeMe() :_straggler(-1)
{}

//custom mycomparison function to sort by second
// struct myComparison
// {
//     bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const
//     {
//         return a.second < b.second;
//     }
// };

template <typename A, typename B>
PmergeMe<A, B>::PmergeMe(const int &argc, char **argv): _straggler(-1)
{
	/**
	 * @brief prints before and after, before time is started
	 * 
	 */
	pre_print_info(argc, argv);
	// {
	// 	std::string check;
	// 	const std::string valid = "0123456789";
	// 	long long int int_check;
	// 	A numbers;
	// 	for (int i = 1; i < argc; i++)
	// 	{
	// 		check = argv[i];
	// 		// std::cout << check << std::endl;
	// 		for (std::string::iterator it = check.begin(); it!= check.end(); it++)
	// 		{
	// 			if (valid.find(*it) == std::string::npos)
	// 				throw PmergeMe<A, B>::invalidInputException();
	// 		}
	// 		int_check = atoll(argv[i]);
	// 		if (int_check > INT_MAX)
	// 			throw std::invalid_argument("Error: Inputs are more than max int");
	// 		numbers.push_back(atoi(argv[i]));
	// 	}
	// 	if (std::is_sorted(numbers.begin(), numbers.end()))
	// 		throw PmergeMe<A, B>::isSortedException();
	// 	std::cout << "Before: ";
	// 	if (numbers.size() <= 5)
	// 	{
	// 		for (size_t i = 0; i < numbers.size(); i++)
	// 			std::cout << numbers[i] << " ";
	// 		std::cout << std::endl;
	// 	}
	// 	else
	// 	{
	// 		for (int i = 0; i < 4;i++)
	// 			std::cout << numbers[i] << " ";
	// 		std::cout << "[...]" << std::endl;
	// 	}
	// 	std::cout << "After: ";
	// 	std::sort(numbers.begin(), numbers.end());
	// 	if (numbers.size() <= 5)
	// 	{
	// 		for (size_t i = 0; i < numbers.size(); i++)
	// 			std::cout << numbers[i] << " ";
	// 		std::cout << std::endl;
	// 	}
	// 	else
	// 	{
	// 		for (int i = 0; i < 4;i++)
	// 			std::cout << numbers[i] << " ";
	// 		std::cout << "[...]" << std::endl;
	// 	}
	// }
	//make jacobsthal seq outside because its not part of sorting or data management
	std::vector<int> jacobsthal;
	make_jacobs_sequences((argc / 2), jacobsthal);
	//translates numbers to indices
	for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); it++)
		*it = *it -1;
	double startTime = getProcessorTime();
	// check for only digits in argv, and push all back to int vector
	std::string check;
	std::string valid = "0123456789";
	A numbers;
	for (int i = 1; i < argc; i++)
	{
		check = argv[i];
		// std::cout << check << std::endl;
		for (std::string::iterator it = check.begin(); it!= check.end(); it++)
		{
			if (valid.find(*it) == std::string::npos)
				throw PmergeMe<A, B>::invalidInputException();
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
	 * @brief assign numbers to vecPairs to first and second, pairing the values.
	 * 
	 */
	B vecPairs;
	typename A::iterator it_next = numbers.begin();
	typename A::iterator it_current = it_next++;
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
	for (typename B::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
	{
		if (it->first > it->second)
		{
			std::swap(it->first, it->second);
		}
	}
	// Sorts vecPairs
	std::sort(vecPairs.begin(), vecPairs.end(), myComparison);
	//re-insert straggler at end of numbers container
	//add straggler to vecPairs
	if (this->_straggler > -1)
	{
		vecPairs.push_back(std::make_pair(this->_straggler, -1));
		numbers.push_back(this->_straggler);
	}
	// put vecPairs second into main chain
	A main_chain;
	for (typename B::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
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
			main_chain.insert(main_chain.begin() + insert_pos, vecPairs.at(*it).first);
		}
	} 
	double endTime = getProcessorTime();

    // Calculate the difference in time
    double timeDifference = endTime - startTime;

    // Output the time difference
	output_print(numbers, timeDifference);
}

template <typename A, typename B>
PmergeMe<A, B>::PmergeMe(PmergeMe<A, B> const& obj): _straggler(obj._straggler)
{}

template <typename A, typename B>
PmergeMe<A, B>& PmergeMe<A, B>::operator=(PmergeMe<A, B> const& obj)
{
	if (this != &obj)
	{
		this->_straggler = obj.getStraggler();
	}
	return (*this);
}

template <typename A, typename B>
PmergeMe<A, B>::~PmergeMe()
{}

template <typename A, typename B>
int PmergeMe<A, B>::getStraggler()const
{
	return (this->_straggler);
}

//Exceptions

template <typename A, typename B>
const char*	PmergeMe<A, B>::invalidInputException::what() const throw()
{
	return ("Error: Invalid Input. Only positive digits are allowed, without spaces.");
}

template <typename A, typename B>
const char*	PmergeMe<A, B>::isSortedException::what() const throw()
{
	return ("Error: Already Sorted");
}

//	PRIVATE MEMBER FUNCTIONS

template <typename A, typename B>
double PmergeMe<A, B>::getProcessorTime() const
{
    std::clock_t currentTime = std::clock();
    double processorTime = static_cast<double>(currentTime) / CLOCKS_PER_SEC * SEC_TO_MS;
    return processorTime;
}


template <typename A, typename B>
int PmergeMe<A, B>::binarySearch(const A &a, const int &item, const int low, const int high)const
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

template <typename A, typename B>
void PmergeMe<A, B>::output_print(const A& container, const double &timeDifference)const
{
	if (typeid(container) == typeid(std::deque<typename A::value_type, typename A::allocator_type>))
	{
		std::cout << "Time to process a range of " << container.size()
			  	  << " elements with std::deque : " 
			  	  <<  timeDifference << " us" << std::endl;
	}
	else if (typeid(container) == typeid(std::vector<typename A::value_type, typename A::allocator_type>))
	{
		std::cout << "Time to process a range of " << container.size()
		  		  << " elements with std::vector : " 
		  		  <<  timeDifference << " us" << std::endl;
	}
}

template <typename A, typename B>
void	PmergeMe<A, B>::pre_print_info(const int &argc, char **argv)
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
				throw PmergeMe<A, B>::invalidInputException();
		}
		int_check = atoll(argv[i]);
		if (int_check > INT_MAX)
			throw std::invalid_argument("Error: Inputs are more than max int");
		numbers.push_back(atoi(argv[i]));
	}
	if (std::is_sorted(numbers.begin(), numbers.end()))
		throw PmergeMe<A, B>::isSortedException();
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

#endif
