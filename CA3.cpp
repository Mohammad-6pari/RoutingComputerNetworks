#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>

#define SEPERATOR   ' '
#define CONTINUE    "continue"
#define EXIT    "exit"
#define TOPOLOGY    "topology"
#define NODE_SEPERATOR  '-'
#define SHOW    "show"
#define MODIFY  "modify"
using namespace std;

int graphSize = 1000;
vector<Node> graph(graphSize);

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

void addEdge(int node1, int node2, int cost) {
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

void printGraph() {
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

tuple<int,int,int> parseTopologyCommand(const string& input){
    istringstream iss(input);

    string token;
    int node1, node2, cost;

    getline(iss, token, NODE_SEPERATOR);
    node1 = stoi(token);

    getline(iss, token, NODE_SEPERATOR);
    node2 = stoi(token);

    getline(iss, token, NODE_SEPERATOR);
    cost = stoi(token);

    return make_tuple(node1, node2, cost);

}

void printAdjacencyMatrix() {
    int numNodes = graph.size();

    vector<vector<int>> adjacencyMatrix(numNodes, vector<int>(numNodes, 0));

    for (const Node& node : graph) {
        int nodeId = node.id;
        for (const Edge& edge : node.neighbors) {
            int neighborId = edge.neighbor;
            int cost = edge.cost;
            adjacencyMatrix[nodeId][neighborId] = cost;
            adjacencyMatrix[neighborId][nodeId] = cost;
        }
    }

    for (const vector<int>& row : adjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int processInput(vector<string> parsedCommand){
    string command= (parsedCommand.size()>0)? parsedCommand[0] : CONTINUE;
    if (command==TOPOLOGY){
        graphSize= parsedCommand.size()+1;
        graph.resize(graphSize);
        graph.clear();
        for (int i = 0; i < graphSize; i++) {
            graph[i].id = i;
        }

        for(int i=1;i<parsedCommand.size();i++){
            string currInp = parsedCommand[i];
            int node1, node2, cost;
            tie(node1, node2, cost) = parseTopologyCommand(currInp);

            if (node1==node2){
                cout << "wrong input. source and destination node are equal.\n";
            } else{
                addEdge(node1,node2,cost);
                cout << "OK\n";
            }
        }
        return 1;

    } else if (command==SHOW){
        printAdjacencyMatrix();
        return 1;

    } else if (command==MODIFY){
        string currInp = parsedCommand[1];
        int node1, node2, cost;
        tie(node1, node2, cost) = parseTopologyCommand(currInp);

        if (node1==node2){
            cout << "ERROR\n";
        } else{
            addEdge(node1,node2,cost);
            cout << "OK\n";
        }
        return 1;

    } else if (command==CONTINUE){
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

    int currAns=1;
    while(currAns==1){
    vector<string> currInput;
    currInput = getInput();
    currAns = processInput(currInput);
    }
    return 0;

}