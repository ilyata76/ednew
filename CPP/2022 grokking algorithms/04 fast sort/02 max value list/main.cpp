#include <iostream>
#include <list>

int maxValue(std::list<int>::const_iterator begin, 
             std::list<int>::const_iterator end) {
    if (begin == end) 
        return 0;

    auto value = *begin;
    return std::max(value, maxValue(++begin, end)); // begin++ будет запаздывать
                                                    // а ++begin будет менять вообще все аргументы в max
}

int main() {
    try {

        std::list<int> lst = {1, 2, 521'1, 3, 4, 5, 6, 7, 50, 100, -1, 1253, 2222};
        
        std::cout << maxValue(lst.begin(), lst.end());
        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}