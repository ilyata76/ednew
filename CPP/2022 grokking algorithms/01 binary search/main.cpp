#include <iostream>
#include <vector>

// для начала простенький с индексом в int-массиве
// самый классически
int binary_search(std::vector<int> array, int item) {
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




int main() {
    try {
        std::vector<int> ary = { 1, 2, 3, 4, 5, 6 };

        auto index = binary_search(ary, 6);

        std::cout << index;

        return 0;
    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}