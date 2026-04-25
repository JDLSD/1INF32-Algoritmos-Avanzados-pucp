#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Edge {
    char target;
    int cost;
};

struct Node {
    char id;
    vector<Edge> edges;
};

bool SearchRec(char currentId, char targetId, int &totalCost,map<char, Node> graph) {
    if (currentId == targetId) return true;
    Node &currentNode = graph[currentId];

    if (currentNode.edges.empty()) return false;

    // Voraz: Ordenar aristas por menor costo
    std::sort(currentNode.edges.begin(), currentNode.edges.end(), [](const Edge &a, const Edge &b) {
        return a.cost < b.cost;
    });

    Edge bestEdge = currentNode.edges[0];
    totalCost += bestEdge.cost;

    //cout << "Visitando: " << currentId << " -> " << bestEdge.target << " (costo: " << bestEdge.cost << ")" << endl;

    return SearchRec(bestEdge.target, targetId, totalCost,graph);
}

int main() {
    map<char, Node> graph;
    graph['A'] = {'A', {{'B', 4}, {'C', 5}, {'D', 6}}};
    graph['B'] = {'B', {{'E', 2}}};
    graph['C'] = {'C', {{'H', 3}}};
    graph['D'] = {'D', {{'F', 3}}};
    graph['E'] = {'E', {{'G', 10}}};
    graph['F'] = {'F', {{'G', 2}}};
    graph['G'] = {'G', {}};
    graph['H'] = {'H', {}};

    int totalCost = 0;
    char inicio = 'A', fin = 'G';

    if (SearchRec(inicio, fin, totalCost,graph)) {
        cout << "Resultado: Ruta encontrada de " << inicio << " a " << fin << endl;
        cout << "Tiempo de viaje: " << totalCost <<" min"<< endl;
    } else {
        cout << "\nNo se encontro una solucion" << endl;
    }

    return 0;
}
