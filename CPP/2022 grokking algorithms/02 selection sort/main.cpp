#include <iostream>
#include <vector>

// сначала для интиков
std::vector<int>::const_iterator findSmallest(std::vector<int>::const_iterator begin,
                                              std::vector<int>::const_iterator end) {
    int smallest = *begin;
    auto it = begin;

    for (auto elem = begin; elem != end; elem++) {
        if (*elem < smallest) {
            smallest = *elem;
            it = elem;
        }
    }

    return it;
}

// сначала для интиков
std::vector<int> selectionSort(std::vector<int>& array) {
    std::vector<int> result;
    result.reserve(array.size());
    
    while(!array.empty()) {
        auto x = findSmallest(array.begin(), array.end());
        result.push_back(*x);
        array.erase(x);
    }

    return result;
}


int main() {
    try {
        
        std::vector<int> arr{-5, -3, 1, -2, 6, 4};

        for (const auto& x : arr) {
            std::cout << x << " ";
        } std::cout << std::endl;

        auto res = selectionSort(arr);

        for (const auto& x : res) {
            std::cout << x << " ";
        }

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}