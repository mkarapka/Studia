#include <iostream>
#include <unordered_map>
#include <string>
#include <list>

using namespace std;

struct Edge
{
    string target;
    double weight;

    Edge(string t, double w) : target(t), weight(w) {}
};

class WGraph
{
private:
    unordered_map<string, list<Edge>> adjacency;

    void removeEdgeWithVertex(list<Edge>& edges, const string& rmId)
    {
        for(auto it = edges.begin(); it != edges.end(); )
        {
            if(it->target == rmId)
                it = edges.erase(it); 
            else
                ++it;
        }
    }

public:
    auto getAdjacency() const
    {
        return adjacency;
    }

    void addVertex(const string& id)
    {
        adjacency.emplace(id, list<Edge>{});
    }

    void removeVertex(const string& id)
    {
        auto neighborsOfV = adjacency[id];
        adjacency.erase(id);

        for(auto v : neighborsOfV)
        {
            removeEdgeWithVertex(adjacency[v.target], id);
        }

    }

    void addEdge(const string& from, const string& to, double weight)
    {
        adjacency[from].emplace_back(to, weight);
        adjacency[to].emplace_back(from, weight);
    }

    void removeEdge(const string& from, const string& to)
    {
        removeEdgeWithVertex(adjacency[from], to);
        removeEdgeWithVertex(adjacency[to], from);
    }
};

ostream& operator<<(ostream& os, const WGraph& graph)
{
    for (const auto& [id, edges] : graph.getAdjacency()) {
        os << id << ": ";
        for (const auto& edge : edges) {
            os << "(" << edge.target << ", " << edge.weight << ") ";
        }
        os << "\n";
    }
    return os;
}

int main() 
{
    WGraph g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 7);
    g.addEdge("B", "C", 1);
    g.addEdge("B", "D", 5);
    g.addEdge("C", "D", 2);

    std::cout << "Lista sąsiadów:\n";
    cout << g;

    g.removeEdge("B", "C");
    g.removeVertex("C");

    std::cout << "\nPo usunięciu krawędzi B–C i wierzchołka C:\n";
    cout << g;
}