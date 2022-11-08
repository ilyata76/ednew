#include <iostream>
#include <vector>

std::vector<int> quickSort(std::vector<int> array) {
    auto size = array.size();
    if (size == 1 || size == 0)
        return array;
    else {
        auto mid = (size-1)/2 ;
        auto elem = array[mid];

        std::vector<int> less;
        std::vector<int> greater;

        for (const auto& x : array) {
            if (x < elem)
                less.push_back(x);
            else if (x > elem)
                greater.push_back(x);
        }

        auto sorted_less = quickSort(less);
        auto sorted_greater = quickSort(greater);

        sorted_less.push_back(elem);
        sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());
        
        return sorted_less;

    }




}


int main() {
    try {

        std::vector<int> array = {1, 2, 5211, 3, 4, 5, 6, 7, 50, 100, -1, 1253, 2222};

        auto sorted_array = quickSort(array);

        for (const auto x : sorted_array) {
            std::cout << x << " ";
        }

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}