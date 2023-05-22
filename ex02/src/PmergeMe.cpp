#include "../include/PmergeMe.hpp"

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

bool myComparison(const std::pair<int, int>&a, const std::pair<int, int>&b)
{
	return (a.second < b.second);
}
