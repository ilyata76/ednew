#include <iostream>
#include <vector>


// 
int recursiveSum(std::vector<int>::const_iterator begin,
                 std::vector<int>::iterator end) {
    if (begin == end) {
        return 0;
    } else {
        return *begin + recursiveSum(begin + 1, end);
    }
}

template<typename T>
T recursiveSum_t(std::vector<T> array) {
    
    
    if (array.begin() == array.end()) {
        return 0;
    } else {
        auto x = array.begin();
        auto value = *x;
        array.erase(x);
        return value + recursiveSum_t(array);
    }

}

int main() {
    try {
        
        std::vector<int> array{ 1, 2, 3, 4, 5, 6, 7 };
        std::vector<double> array_double{ 1.0, 2.5, 3.5, 4.1, 5.3, 6.4, 7.8 };

        std::cout << recursiveSum(array.begin(), array.end()) << std::endl;
        std::cout << recursiveSum_t<int>(array) << std::endl;
        std::cout << recursiveSum_t<double>(array_double) << std::endl;
        

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}