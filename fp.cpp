#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <algorithm>

struct Module {
    int id;
    int width;
    int height;
    int x = 0; // Lower-left corner x-coordinate
    int y = 0; // Lower-left corner y-coordinate
};

// HCG VCG
void buildGraph(int n, const std::vector<int> &positive_sequence, const std::vector<int> &negative_sequence,std::unordered_map<int, std::set<int>> &HCG, std::unordered_map<int, std::set<int>> &VCG) {
    std::unordered_map<int, int> pos_index, neg_index;
    for (int i = 0; i < n; ++i) {
        pos_index[positive_sequence[i]] = i;
        neg_index[negative_sequence[i]] = i;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int u = positive_sequence[i];
            int v = positive_sequence[j];
            if (neg_index[u] < neg_index[v]) {
                HCG[u].insert(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int u = negative_sequence[i];
            int v = negative_sequence[j];
            if (pos_index[u] > pos_index[v]) {
                VCG[u].insert(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        HCG[0].insert(positive_sequence[i]);
        VCG[0].insert(negative_sequence[i]);
        HCG[positive_sequence[i]].insert(n + 1);
        VCG[negative_sequence[i]].insert(n + 1);
    }
}

// 移除冗余边的函数（适用于 HCG 和 VCG）
/*void removeRedundantEdges(std::unordered_map<int, std::set<int>> &graph) {
    for (auto &[node, neighbors] : graph) {
        std::vector<int> to_remove;
        for (int neighbor : neighbors) {
            std::queue<int> q;
            q.push(node);
            std::unordered_set<int> visited;
            visited.insert(node);
            bool found_indirect_path = false;

            while (!q.empty() && !found_indirect_path) {
                int current = q.front();
                q.pop();
                for (int next : graph[current]) {
                    if (next == neighbor && current != node) {
                        found_indirect_path = true;
                        break;
                    }
                    if (visited.insert(next).second) {
                        q.push(next);
                    }
                }
            }

            if (found_indirect_path) {
                to_remove.push_back(neighbor);
            }
        }

        for (int redundant_neighbor : to_remove) {
            neighbors.erase(redundant_neighbor);
        }
    }
}*/

// topo
void topo(std::unordered_map<int, std::set<int>> &graph,
                                            std::unordered_map<int, Module> &modules, bool isHorizontal) {
    std::unordered_map<int, int> inDegree;
    for (const auto &[node, neighbors] : graph) {
        for (int neighbor : neighbors) {
            inDegree[neighbor]++;
        }
    }

    std::queue<int> q;
    q.push(0);  // 从0开始

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
            int newCoordinate = (isHorizontal ? modules[node].x + modules[node].width : modules[node].y + modules[node].height);
            if (isHorizontal) {
                modules[neighbor].x = std::max(modules[neighbor].x, newCoordinate);
            } else {
                modules[neighbor].y = std::max(modules[neighbor].y, newCoordinate);
            }

            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
}

// 计算布局的宽度和高度
std::pair<int, int> cal(const std::unordered_map<int, Module> &modules) {
    int layout_width = 0;
    int layout_height = 0;
    for (const auto &[id, module] : modules) {
        layout_width = std::max(layout_width, module.x + module.width);
        layout_height = std::max(layout_height, module.y + module.height);
    }
    return {layout_width, layout_height};
}

// 打印布局的宽度和高度以及模块的最终位置
void printt(const std::unordered_map<int, Module> &modules, int n) {
    auto [layout_width, layout_height] = cal(modules);
    std::cout << layout_width << " " << layout_height << "\n";

    for (int id = 1; id <= n; ++id) {
        const auto &module = modules.at(id);
        std::cout << module.x << " " << module.y << "\n";
    }
    /*for (const auto &[id, module] : modules) {
        std::cout << module.x << " " << module.y << "\n";
    }*/

    
    /*std::cout << "Module positions (lower-left corner):\n";
    for (const auto &[id, module] : modules) {
        std::cout << "Module " << id << ": (" << module.x << ", " << module.y << ")\n";
    }*/
    
}



/*void printGraph(const std::unordered_map<int, std::set<int>> &graph, const std::string &graphName) {
    std::cout << graphName << ":\n";
    for (const auto &[node, edges] : graph) {
        std::cout << "Module " << node << " -> ";
        for (int neighbor : edges) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}*/

void parseInput(int &n, std::vector<int> &positive_sequence, std::vector<int> &negative_sequence, std::unordered_map<int, Module> &modules) {
    std::cin >> n;

    positive_sequence.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> positive_sequence[i];
    }

    negative_sequence.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> negative_sequence[i];
    }

    for (int i = 0; i < n; ++i) {
        int id, width, height;
        std::cin >> id >> width >> height;
        modules[id] = {id, width, height, 0, 0};
    }
}

int main() {
    int n;
    std::vector<int> positive_sequence, negative_sequence;
    std::unordered_map<int, Module> modules;

    parseInput(n, positive_sequence, negative_sequence, modules);

    std::unordered_map<int, std::set<int>> HCG, VCG;
    buildGraph(n, positive_sequence, negative_sequence, HCG, VCG);

    //removeRedundantEdges(HCG);
    //removeRedundantEdges(VCG);

    //printGraph(HCG, "HCG");
    //printGraph(VCG, "VCG");

    topo(HCG, modules, true);  
    topo(VCG, modules, false); 

    printt(modules, n);

    return 0;
}


