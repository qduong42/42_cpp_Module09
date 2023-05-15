#include <vector>
#include <iostream>
#include <cmath>
int main(int argc, char **argv)
{
	std::vector<int> jacob;
	int n = argc - 2;
	std::cout << "n:" << n << std::endl;
	jacob.push_back(0);
	int i;
	i = 0;
	while (n)
	{
		jacob.push_back(2 * jacob.back() + pow(-1, i));
		std::cout << "pushed number" << jacob.back() << std::endl;
		n--;
		i++;
	}
    for (std::vector<int>::iterator it = jacob.begin(); it != jacob.end(); ++it) {
        std::cout << *it << std::endl;
    }
	return 0;
}
