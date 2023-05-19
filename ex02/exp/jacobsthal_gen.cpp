#include <vector>
#include <iostream>
#include <cmath>

int	jacobsthalNumber(int idx)
{
	int	jacobsthal;
	jacobsthal = jacobsthalNumber(idx - 1) + 2 * jacobsthalNumber(idx - 2);
	return (jacobsthal);
}

void make_jacobs_sequence(std::vector<std::pair<int, int > >& paired_vectr, std::vector<int>& jacobs_num)
{
    int i = 3;
    jacobs_num.push_back(1);

    while(std::find(jacobs_num.begin(), jacobs_num.end(), paired_vectr.size()) == jacobs_num.end()){
        int num = jacobsthalNumber(i++);
        jacobs_num.push_back(num);
		std::cout << "1st while" << num << std::endl;
        while (std::find(jacobs_num.begin(), jacobs_num.end(), --num) == jacobs_num.end())
        {
            jacobs_num.push_back(num);
			std::cout << "2nd while" << num << std::endl;
        }
    }
}

// std::vector<int> jacobsthal(int limit)
// {
// 	int jacobsthalIndex = 2;
// 	int x;
// 	std::vector<int> jacob;
// 	while (jacobsthalNumber(jacobsthalIndex) < limit)
// 	{
// 		x = jacobsthalNumber(jacobsthalIndex);
// 		jacob.push_back(jacobsthalNumber(jacobsthalIndex));
// 		while ((x - 1)> 0 && x - 1 != jacobsthalNumber(jacobsthalIndex - 1))
// 		{
// 			jacob.push_back(x - 1);
// 			x--;
// 		}
// 		jacobsthalIndex++;
// 	}
// 	jacob.push_back(jacobsthalNumber(jacobsthalIndex));
// 	x = jacobsthalNumber(jacobsthalIndex);
// 	while ((x - 1)> 0 && x - 1 != jacobsthalNumber(jacobsthalIndex - 1))
// 	{
// 			jacob.push_back(x - 1);
// 		x--;
// 	}
// 	return (jacob);
// }

int main(int argc, char **argv)
{
	std::vector<int> jacobs;
	// int n = argc - 2;
	// std::cout << "n:" << n << std::endl;
	// jacob.push_back(0);
	// int i;
	// i = 0;
	// while (n)
	// {
	// 	jacob.push_back(2 * jacob.back() + pow(-1, i));
	// 	std::cout << "pushed number" << jacob.back() << std::endl;
	// 	n--;
	// 	i++;
	// }
	// int i = ((argc - 1)/2) + 1;
	// std::cout << i << std::endl;
	jacobs = make_jacobs_sequence(((argc - 1)/2) + 1);
    for (std::vector<int>::iterator it = jacobs.begin(); it != jacobs.end(); ++it) {
        std::cout << *it << std::endl;
    }
	return 0;
}

