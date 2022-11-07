#include <iostream>
#include <vector>

template<typename T>
int binary_search(const std::vector<T>& array, 
                  const T& item);

// для начала простенький с индексом в int-массиве
// самый классически
template<typename int>
int binary_search(const std::vector<int>& array, 
                  int item) {
    size_t low = 0;
    size_t high = array.size() - 1;

    while (high >= low) {
        size_t mid = (low + high) / 2;
        int guess = array[mid];

        if (guess == item)
            return mid;
        else if (guess > item) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    throw std::exception("<error>");
    
};

template<typename T>
int binary_search(const std::vector<T>& array, 
                  const T& item) {
    size_t low = 0;
    size_t high = array.size() - 1;

    while (low <= high) {
        size_t mid = (low + high) / 2;
        T guess = array[mid];

        if (guess < item)
            low = mid + 1;
        else if (guess > item)
            high = mid - 1;
        else 
            return mid;
    }

    throw std::exception("<error>");
}


int main() {
    try {
        std::vector<int> int_ary = { 1, 2, 3, 4, 5, 6 };
        std::vector<double> double_ary = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
        int item = 5;

        auto index = binary_search(int_ary, item);
        std::cout << index;
        
        index = binary_search<double>(double_ary, static_cast<double>(item));
        std::cout << index;

        return 0;
    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}