#include "../include/RPN.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Enter 2 args" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
