#include <vector>
#include <iostream>

int binarySearch(std::vector<int>& vec, int item, int low, int high)
{
    if (high <= low) {
        if (item > vec[low])
            return low + 1;
        else
            return low;
    }
    
    int mid = low + (high - low) / 2;
    
    if (item == vec[mid])
        return mid + 1;
    else if (item > vec[mid])
        return binarySearch(vec, item, mid + 1, high);
    else
        return binarySearch(vec, item, low, mid - 1);
}

int main()
{
    std::vector<int> vec = {1, 3, 5, 7, 9};
    int item = 4;

    int insertPos = binarySearch(vec, item, 0, vec.size() - 1);
    vec.insert(vec.begin() + insertPos, item);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
    return 0;
}