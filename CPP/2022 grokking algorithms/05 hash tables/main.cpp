#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, bool> voted;

void check_voter(const std::string& name) {
    using std::cout;
    using std::endl;

    auto search = voted.find(name);
    if (search == voted.end() || search->second == false) {
        voted.insert({ name, true });
        cout << "Let them vote!" << endl;;
    }
    else {
        cout << "Kick them out!" << endl;
    }
}


int main() {
    try {
        
        std::unordered_map<std::string, float> book = {
            {"apple", 0.67},
            {"milk", 1.49},
            {"avocado", 1.49}
        };

        for (std::pair<std::string, float> pair : book) {
            std::cout << pair.first << ": " << pair.second << "$" << std::endl;
        }

        check_voter("tom");
        check_voter("mike");
        check_voter("mike");

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}