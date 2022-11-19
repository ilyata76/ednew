#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

inline bool is_seller(const std::string& name) {
    return name.back() == 'm';
}


std::string search(const std::string& name, const std::unordered_map<std::string, std::vector<std::string>> graph) {
    std::queue<std::string> search_queue;
    std::unordered_set<std::string> searched_persons;

    for (const auto& x : graph.find(name)->second) {
        search_queue.push(x);
    };
    
    while (!search_queue.empty()) {
        std::string person = search_queue.front();
        search_queue.pop();

        if (searched_persons.find(person) == searched_persons.end()) { // если он ещё не проверен
            
            if (is_seller(person)) {
                return person;
            } else {
                for (const auto& x : graph.find(person)->second) {
                    search_queue.push(x);
                }
                searched_persons.insert(person);
            }

        }

    };

};


int main() {
    try {
        
        std::unordered_map<std::string, std::vector<std::string>> graph;
        graph.insert({ "you", {"alice", "bob", "claire"} });
        graph.insert({ "bob", {"anuj", "peggy"} });
        graph.insert({ "alice", {"peggy"} });
        graph.insert({ "claire", {"thom", "jonny"} });
        graph.insert({ "anuj", {} });
        graph.insert({ "peggy", {} });
        graph.insert({ "thom", {} });
        graph.insert({ "jonny", {} });


        std::string name = "you";
        std::cout << search(name, graph);

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}