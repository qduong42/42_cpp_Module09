#include "../include/PmergeMe.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	PmergeMe seq;
	try
	{
		PmergeMe try_create(argc, argv);
		seq = try_create;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
