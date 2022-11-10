#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

int main() {
    try {
        
        using node = std::string; // ����
        using node_cost_table = std::unordered_map<node, unsigned int>; // �������, ������� ������ �� ��������� ����� ��������� ���� �� ���
        using graph_table = std::unordered_map<node, node_cost_table>; // ����� ������� ��� ���� - ���� � ������� ��� �� ����������� �� ��������� ���� �� ������� ����
        using parent_table = std::unordered_map<node, node>; // ��� ���������� ������������ ���� ����� ������� ��������� ����� ����� ������

        graph_table graph;
        graph.reserve(4U);
        graph.emplace("start", node_cost_table{ {"a", 6}, {"b", 2} }); // ����� ������� �� a � �� b
        graph.emplace("a", node_cost_table{ {"finish", 1} }); // a ������� �� finish
        graph.emplace("b", node_cost_table{ {"a", 3},{"finish", 5} }); // b - �� a � �� finish
        graph.emplace("finish", node_cost_table{}); // finish

        // ������ �������� ������� ��������� ����� �� ��������� �����
        node_cost_table global_costs{ {"a", 6} ,{"b", 2}, {"finish", UINT32_MAX} };

        // ������ �������� ������� ��� ��������� ����� ������
        parent_table parents{ {"a", "start"}, {"b", "start"} };

        // ������ ����� ���������� ����, ������� ���� ��������
        std::unordered_set<node> visited;
        visited.reserve(4u);

        // �������� ������� ������ ��������� ������������ ����
        auto findLowestCostNode = [&visited](node_cost_table costs) {
            auto lower_cost = UINT32_MAX;
            node lowest_cost_node{};

            for (const auto& node_cst_table : costs) { // ��� ���� ������ ������ ����-���������
                node current_node = node_cst_table.first;
                unsigned current_node_cost = node_cst_table.second;

                if (visited.find(current_node) == visited.end()) { // ���� �� ��������
                    if (current_node_cost < lower_cost) { // � ���� ��������� ��������� ������ �������
                        lower_cost = current_node_cost; // ������
                        lowest_cost_node = current_node;
                    }
                }
            }
            return lowest_cost_node; // � ����������
        };

        auto current_node = findLowestCostNode(global_costs); // ������� ����� ��������� ����

        while (!current_node.empty()) { // ���� �� �� ����� �� ���� ��� ������ 
            //(� ������ ������ ��� ����� ��������� ���� (�.�. ���� ��� ���� �� ����� �������� ��� �� ��������� ����))
            // �.�. ���� ������ ���� ����� ������, ��� ������ ���������� + ���_�����_�����, �� � ������ �������� � ���� ���

            auto current_cost = global_costs[current_node]; // ������� ����������� ��������� �� ����
            auto neighbours = graph[current_node]; // � ���������� ����� ���������� �����

            for (const auto& neighbour : neighbours) {
                auto neighbour_new_global_cost = neighbour.second + current_cost; // ������� + �� ����������
                node neighbour_node = neighbour.first;

                if (neighbour_new_global_cost < global_costs[neighbour_node]) { // ���� ��������� ����, ��� �� ������
                    global_costs[neighbour_node] = neighbour_new_global_cost;
                    parents[neighbour_node] = current_node;
                }

            }
            // ��������, ��� ��� ���� �����
            visited.insert(current_node);

            // � ���� ����� ����
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