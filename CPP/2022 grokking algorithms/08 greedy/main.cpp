#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


std::unordered_set<std::string> intersection(const std::unordered_set<std::string>& a, 
                                             const std::unordered_set<std::string>& b) {
    std::unordered_set<std::string> result;

    for (const auto& x : a) {
        for (const auto& y : b) {
            if (x == y)
                result.insert(x);
        }
    }
    
    return result;

};

void operator -= (std::unordered_set<std::string>& a,
                  const std::unordered_set<std::string>& b) {
    for (auto j = b.begin(); j != b.end(); ++j)
        for (auto i = a.begin(); i != a.end(); )
            if (*i == *j) 
                i = a.erase(i);
            else 
                ++i;
}

int main() {
    try {

        std::unordered_set<std::string> states_needed({ "mt", "wa", "or", "id", "nv", "ut", "ca", "az" });

        std::unordered_map<std::string, std::unordered_set<std::string>> stations;
        stations.insert({ "kone", {"id", "nv", "ut"} });
        stations.insert({ "ktwo", {"wa", "id", "mt" } });
        stations.insert({ "kthree", {"or", "nv", "ca" } });
        stations.insert({ "kfour", {"nv", "ut" } });
        stations.insert({ "kfive", {"ca", "az" } });

        std::unordered_set<std::string> final_stations;
        

        while (!states_needed.empty()) {
            std::string best_station;
            std::unordered_set <std::string> states_covered;
            for (const auto& x : stations) {
                std::unordered_set<std::string> coverage = intersection(x.second, states_needed);
                if (coverage.size() > states_covered.size()) {
                    best_station = x.first;
                    states_covered = coverage;
                }
            }
            states_needed -= states_covered;
            final_stations.insert(best_station);
        }

        for (const auto& x : final_stations)
            std::cout << x << std::endl;

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}