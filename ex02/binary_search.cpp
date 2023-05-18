#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int binarySearch(std::vector<int> &a, int item, int low, int high)
{
    if (high <= low) {
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

void binary_search(std::vector<int> &a)

int main()
{
	std::vector <int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};
	// std::vector <int>::iterator it = a.begin();
	// std::advance(it, 2);
	// std::cout << *it << std::endl;
	// a.insert(it, 1000);
	binary_search(a)
	for (std::vector <int> ::iterator ite = a.begin(); ite != a.end();ite++)
	{
		std::cout << *ite << std::endl;
	}
	return 0;
}