#include <iostream>
#include <sstream>
#include <vector>

#define SEPERATOR   ' '
#define CONTINUE    "continue"
#define EXIT    "exit"

using namespace std;

struct Edge{
    int neighbor;
    int cost;
};

struct Node{
    int id;
    vector<Edge> neighbors;
};

bool edgeExists(const vector<Edge>& neighbors, int neighbor) {
    for (const Edge& edge : neighbors) {
        if (edge.neighbor == neighbor) {
            return true;
        }
    }
    return false;
}

void addEdge(vector<Node>& graph, int node1, int node2, int cost) {
    if (edgeExists(graph[node1].neighbors, node2)) {
        // If the edge already exists, update the cost
        for (Edge& edge : graph[node1].neighbors) {
            if (edge.neighbor == node2) {
                edge.cost = cost;
                break;
            }
        }

        for (Edge& edge : graph[node2].neighbors) {
            if (edge.neighbor == node1) {
                edge.cost = cost;
                break;
            }
        }
    } else {
        Edge edge1;
        edge1.neighbor = node2;
        edge1.cost = cost;
        graph[node1].neighbors.push_back(edge1);

        Edge edge2;
        edge2.neighbor = node1;
        edge2.cost = cost;
        graph[node2].neighbors.push_back(edge2);
    }
}

void printGraph(const vector<Node>& graph) {
    for (const Node& node : graph) {
        cout << "Node " << node.id << " Neighbors: ";
        for (const Edge& edge : node.neighbors) {
            cout << edge.neighbor << " (Cost: " << edge.cost << ") ";
        }
        cout << endl;
    }
}

vector<string> getInput(){
    cout << "input command:\n"; 
    string command;
    getline(cin,command);
    stringstream ss(command);
    string s;
    vector<string> parsedCommand;
    while (getline(ss,s,SEPERATOR)){
        if(s.length()>0)
            parsedCommand.push_back(s);
    }
    return parsedCommand;
}

int processInput(vector<string> parsedCommand){
    string command= (parsedCommand.size()>0)? parsedCommand[0] : CONTINUE;
    if (command==CONTINUE){
        cout << "no input found\n";
        return 1;
    } else if (command==EXIT){
        cout << "exit\n";
        return 0;
    } else {
        cout << "invalid input, enter another input or \"help\" for see commands.\n";
        return 1;

    }
}

int main(){

    int maxNodes = 1000;
    vector<Node> graph(maxNodes);
    for (int i = 0; i < maxNodes; i++) {
        graph[i].id = i;
    }

    int currAns=1;
    while(currAns==1){
    vector<string> currInput;
    currInput = getInput();
    currAns = processInput(currInput);
    }


    // addEdge(graph, 0, 1, 2);
    // addEdge(graph, 0, 3, 4);
    // addEdge(graph, 1, 2, 3);
    // addEdge(graph, 1, 3, 1);
    // addEdge(graph, 2, 4, 5);
    // addEdge(graph, 3, 4, 2);

    // Print the neighbors of each node with their costs
    // printGraph(graph);

    // Update the cost of an existing edge
    // addEdge(graph, 0, 1, 5);

    // Print the updated graph
    // cout << "Updated Graph:\n";
    // printGraph(graph);

    return 0;

}