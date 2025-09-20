#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

unordered_map<string, list<string>> read_graph(string filename){
    unordered_map<string, list<string>> graph;
    ifstream file(filename);
    string line;
    string from, to;

    while(getline(file, line)){
        from = line.substr(0, 2);
        to = line.substr(3);

        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    return graph;
}


set<set<string> > find_3_cycles(unordered_map<string, list<string>> graph){
    set<set<string> > result;
    string start = "t";
    // Your implementation here

    for(char c = 'a'; c <= 'z'; ++c) {
        start.push_back(c);
        for(auto neighbour : graph[start]){
            for(auto next_neighbour : graph[neighbour]){
                if(find(graph[next_neighbour].begin(), graph[next_neighbour].end(), start) != graph[next_neighbour].end()){
                    result.insert({start, neighbour, next_neighbour});
                }
            }
        }
        start.pop_back();
    }

    return result;
}


int main(){
    auto graph = read_graph("input23.txt");
    auto cycles = find_3_cycles(graph);

    for(const auto& cycle : cycles){
        for(const auto& node : cycle){
            cout << node << " ";
        }
        cout << endl;
    }
    cout << "Total 3-cycles: " << cycles.size() << endl;

    return 0;
}
