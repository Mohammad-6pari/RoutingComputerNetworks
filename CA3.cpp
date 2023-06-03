#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <fstream>

#define SEPERATOR   ' '
#define CONTINUE    "continue"
#define EXIT    "exit"
#define TOPOLOGY    "topology"
#define NODE_SEPERATOR  '-'
#define SHOW    "show"
#define MODIFY  "modify"
#define NO_PATH_COST    -1
#define ZERO    0
#define REMOVE  "remove"
using namespace std;


struct Edge{
    int neighbor;
    int cost;
};

struct Node{
    int id;
    vector<Edge> neighbors;
};

int graphSize = 1000;
vector<Node> graph(graphSize);

bool edgeExists(const vector<Edge>& neighbors, int neighbor) {
    for (const Edge& edge : neighbors) {
        if (edge.neighbor == neighbor) {
            return true;
        }
    }
    return false;
}

void removePath(int node1, int node2) {
    if (node1 >= 0 && node1 < graphSize && node2 >= 0 && node2 < graphSize) {
        for (size_t i = 0; i < graph[node1].neighbors.size(); i++) {
            if (graph[node1].neighbors[i].neighbor == node2) {
                graph[node1].neighbors.erase(graph[node1].neighbors.begin() + i);
                break;
            }
        }

        for (size_t i = 0; i < graph[node2].neighbors.size(); i++) {
            if (graph[node2].neighbors[i].neighbor == node1) {
                graph[node2].neighbors.erase(graph[node2].neighbors.begin() + i);
                break;
            }
        }
        cout << "OK" << endl;
    } else {
        cout << "Error: Invalid node IDs." << endl;
    }
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

vector<string> getInput(ifstream& input){
    // cout << "input command:\n"; 
    string command;
    getline(input,command);
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

tuple<int,int> parseRemoveCommand(const string& input){
    istringstream iss(input);

    string token;
    int node1, node2;

    getline(iss, token, NODE_SEPERATOR);
    node1 = stoi(token);

    getline(iss, token, NODE_SEPERATOR);
    node2 = stoi(token);

    return make_tuple(node1, node2);

}


void printAdjacencyMatrix() {
    int numNodes = graph.size();

    vector<vector<int>> adjacencyMatrix(numNodes, vector<int>(numNodes, NO_PATH_COST));
    for (int i=0;i<adjacencyMatrix.size();i++)
        adjacencyMatrix[i][i]=0;

    for (const Node& node : graph) {
        int nodeId = node.id;
        for (const Edge& edge : node.neighbors) {
            int neighborId = edge.neighbor;
            int cost = edge.cost;
            adjacencyMatrix[nodeId][neighborId] = cost;
            adjacencyMatrix[neighborId][nodeId] = cost;
        }
    }

    cout << "  | ";
    for (const Node  node : graph){
        cout << node.id << " ";
    }
    cout << "\n----";
    for (int i=0;i<graph.size();i++){
        cout << "--";
    }
    cout << endl;
    int ind=0;
    for (const vector<int>& row : adjacencyMatrix) {
        cout << graph[ind].id<<" | ";
        for (int val : row) {
            cout << val << " ";
        }
        ind++;
        cout<<endl;
    }
}

int processInput(vector<string> parsedCommand){
    string command= (parsedCommand.size()>0)? parsedCommand[0] : CONTINUE;
    if (command==TOPOLOGY){
        graphSize= parsedCommand.size()+1;
        graph.resize(graphSize);
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

    } else if (command==REMOVE) {
        string currInp=parsedCommand[1];
        int node1,node2;
        tie(node1, node2) = parseRemoveCommand(currInp);
        removePath(node1,node2);
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
    ifstream inputFile("inputs.txt");
    if (!inputFile) {
    cout << "Failed to open the input file." << endl;
    return 1;
    }
    
    int currAns=1;
    while(currAns==1){
    vector<string> currInput;
    currInput = getInput(inputFile);
    currAns = processInput(currInput);
    }
    return 0;

}