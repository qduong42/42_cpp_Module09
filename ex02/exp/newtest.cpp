#include <ctime>
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

double getProcessorTime()
{
    std::clock_t currentTime = std::clock();
    double processorTime = static_cast<double>(currentTime) / CLOCKS_PER_SEC;
    return processorTime;
}

int main()
{
std::cout << "=========LINEAR SEARCH + insert==========" << std::endl;
    // Measure the time before the first operation
    double stime = getProcessorTime();
	{
    std::vector<int> vec2 = {813, 838, 70, 319, 785, 559, 360, 384, 193, 628, 930, 884, 916, 496, 305, 400, 844, 419, 36, 710, 648, 212, 607, 737, 786, 507, 861, 279, 697, 131, 945, 509, 716, 362, 942, 502, 711, 322, 425, 683, 385, 621, 598, 83, 550, 440, 890, 88, 406, 815, 553, 351, 698, 34, 751, 781, 252, 236, 874, 775, 807, 704, 35, 15, 171, 269, 839, 120, 512, 37, 646, 107, 78, 879, 574, 499, 493, 915, 265, 722, 9, 800, 172, 4, 121, 2, 346, 871, 774, 391, 779, 105, 373, 776, 465, 544, 538, 679, 97, 827, 937, 952, 671, 905, 917, 667, 257, 797, 691, 173, 521, 836, 189, 277, 280, 157, 46, 482, 578, 501, 313, 285, 589, 310, 608, 976, 10, 475, 273, 26, 505, 647, 380, 65, 64, 588, 139, 44, 66, 31, 525, 164, 552, 523, 379, 766, 14, 777, 947, 348, 964, 94, 314, 359, 643, 85, 867, 161, 530, 963, 461, 840, 652, 948, 140, 175, 872, 862, 481, 476, 834, 577, 223, 579, 618, 416, 995, 24, 842, 958, 641, 541, 662, 389, 7, 791, 736, 453, 338, 614, 294, 894, 219, 365, 292, 118, 483, 237, 303, 609, 981, 549, 746, 491, 678, 344, 355, 288, 728, 772, 446, 642, 571, 721, 990, 435, 715, 301, 258, 616, 442, 484, 625, 526, 60, 902, 418, 123, 997, 712, 980, 508, 922, 762, 312, 650, 778, 591, 111, 649, 878, 299, 151, 993, 167, 548, 213, 176, 547, 281, 177, 720, 534, 478, 434, 403, 353, 430, 692, 96, 601, 780, 554, 546, 784, 829, 533, 760, 316, 387, 561, 939, 174, 283, 495, 802, 956, 332, 462, 234, 661, 701, 317, 949, 47, 211, 910, 896, 632, 203, 93, 137, 801, 494, 887, 883, 488, 448, 363, 903, 684, 231, 826, 238, 469, 444, 615, 537, 339, 331, 134, 415, 75, 192, 788, 186, 586, 1000, 742, 573, 199, 375, 962, 941, 302, 851, 229, 953, 500, 759, 830, 935, 207, 831, 620, 590, 706, 612, 194, 306, 583, 847, 863, 372, 969, 568, 215, 783, 859, 911, 873, 417, 811, 89, 228, 326, 477, 972, 38, 735, 345, 361, 429, 460, 528, 825, 893, 793, 43, 912, 218, 479, 396, 988, 458, 666, 758, 920, 50, 965, 261, 789, 410, 906, 951, 321, 696, 49, 264, 522, 677, 613, 654, 92, 695, 18, 459, 604, 116, 582, 392, 226, 960, 617, 276, 246, 383, 803, 819, 133, 719, 138, 644, 130, 84, 221, 286, 270, 125, 307, 63, 824, 734, 48, 752, 714, 681, 635, 992, 718, 745, 928, 244, 837, 102, 725, 914, 40, 91, 998, 381, 817, 757, 148, 300, 699, 741, 129, 557, 805, 473, 51, 33, 298, 680, 414, 103, 318, 5, 135, 543, 631, 587, 32, 356, 989, 423, 197, 931, 575, 253, 311, 985, 542, 624, 685, 773, 267, 835, 804, 486, 982, 560, 875, 374, 390, 876, 474, 8, 256, 904, 852, 260, 864, 409, 152, 593, 602, 973, 95};
    std::vector<int> side_chain2 = {800, 514, 825, 457, 629, 388, 483, 839, 9, 842, 658, 734, 891, 335, 858, 204, 542, 934, 300, 252, 69, 135};

    // int insertPos = binarySearch(vec, item, 0, vec.size() - 1);
	std::sort(vec2.begin(), vec2.end());
	for (std::vector<int>::iterator it = vec2.begin(); it != vec2.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	// std::cout << vec2.size() << std::endl;
	// for (std::vector<int>::iterator it = side_chain2.begin(); it != side_chain2.end(); it++)
	// {
	// 	// std::vector<int>::iterator insertPos2 = std::upper_bound(vec2.begin(), vec2.end(), *it);
	// 	for (std::vector<int>::iterator ite = vec2.begin(); ite != vec2.end(); ite++)
	// 	{
	// 		if (*ite >= *it)
	// 			vec2.insert(ite, *it);
	// 	}
	// 	// vec2.insert(insertPos2, *it);
	// // for (std::vector<int>::iterator it = vec2.begin(); it != vec2.end(); it++)
	// // {
	// // 	std::cout << *it << std::endl;
	// // }
	// }
    for (std::vector<int>::const_iterator it = side_chain2.begin(); it != side_chain2.end(); ++it)
    {
        // Find the insertion position using a linear search with iterators
        std::vector<int>::iterator insertPos = vec2.begin();
        while (insertPos != vec2.end() && *insertPos < *it)
        {
            ++insertPos;
        }

        // Insert the element at the found position
        vec2.insert(insertPos, *it);
    }

	// std::cout << vec2.size() << std::endl;
	}
    // Perform the first operation
    // Measure the time after the first operation
    double etime = getProcessorTime();
    // Calculate the difference in time
    double tdiff2 = etime - stime;
    // Output the time difference
    std::cout << "LINEAR Time difference: " << tdiff2 << " seconds" << std::endl;
}