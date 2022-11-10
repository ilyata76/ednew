#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

int main() {
    try {
        
        using node = std::string; // узел
        using node_cost_table = std::unordered_map<node, unsigned int>; // таблица, которая хранит от начальной точки стоимость пути до нод
        using graph_table = std::unordered_map<node, node_cost_table>; // будет хранить сам граф - ноду и таблицу нод со стоимостями до следующих узов от текущей ноды
        using parent_table = std::unordered_map<node, node>; // при нахождении оптимального пути будет хранить отношение между этими нодами

        graph_table graph;
        graph.reserve(4U);
        graph.emplace("start", node_cost_table{ {"a", 6}, {"b", 2} }); // старт смотрит на a и на b
        graph.emplace("a", node_cost_table{ {"finish", 1} }); // a смотрит на finish
        graph.emplace("b", node_cost_table{ {"a", 3},{"finish", 5} }); // b - на a и на finish
        graph.emplace("finish", node_cost_table{}); // finish

        // теперь заполним таблицу стоимость путей от начальной точки
        node_cost_table global_costs{ {"a", 6} ,{"b", 2}, {"finish", UINT32_MAX} };

        // теперь создадим таблицу для отношения между узлами
        parent_table parents{ {"a", "start"}, {"b", "start"} };

        // теперь будем запоминать узлы, которые были пройдены
        std::unordered_set<node> visited;
        visited.reserve(4u);

        // создадим функцию поиска ближайшей непосещённой ноды
        auto findLowestCostNode = [&visited](node_cost_table costs) {
            auto lower_cost = UINT32_MAX;
            node lowest_cost_node{};

            for (const auto& node_cst_table : costs) { // для всех данных таблиц нода-стоимость
                node current_node = node_cst_table.first;
                unsigned current_node_cost = node_cst_table.second;

                if (visited.find(current_node) == visited.end()) { // если не посетили
                    if (current_node_cost < lower_cost) { // и если стоимость посещения меньше текущей
                        lower_cost = current_node_cost; // меняем
                        lowest_cost_node = current_node;
                    }
                }
            }
            return lowest_cost_node; // и возвращаем
        };

        auto current_node = findLowestCostNode(global_costs); // выделим самый ближайший узел

        while (!current_node.empty()) { // пока мы не дошли до ноды без связей 
            //(в данном случае это будет последний узел (т.е. пока все узлы не будут обойдены или не достигнем цели))
            // т.е. если второй узел будет дороже, чем первый пройденный + его_сосед_финал, то и смысла заходить в него нет

            auto current_cost = global_costs[current_node]; // текущая минимальная стоимость до узла
            auto neighbours = graph[current_node]; // в глобальном графе определены связи

            for (const auto& neighbour : neighbours) {
                auto neighbour_new_global_cost = neighbour.second + current_cost; // текущая + до следующего
                node neighbour_node = neighbour.first;

                if (neighbour_new_global_cost < global_costs[neighbour_node]) { // если стоимость ниже, чем от старта
                    global_costs[neighbour_node] = neighbour_new_global_cost;
                    parents[neighbour_node] = current_node;
                }

            }
            // помечаем, что уже были здесь
            visited.insert(current_node);

            // и берём новый узел
            current_node = findLowestCostNode(global_costs);

        }

        for (const auto& x : global_costs) {
            std::cout << x.first << " : " << x.second << std::endl;
        }

        for (const auto& x : parents) {
            std::cout << x.first << " : " << x.second << std::endl;
        }

        return 0;

    } catch(std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
}