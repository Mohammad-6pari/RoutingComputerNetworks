#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <fstream>
#include <limits>
#include <queue>
#include <stack>

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
#define LSRP    "lsrp"
#define DVRP    "dvrp"
#define SET_MAX    "set-max"


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
    int flag=1;
    if (node1 >= 0 && node1 < graphSize && node2 >= 0 && node2 < graphSize && node1 != node2) {
        for (size_t i = 0; i < graph[node1].neighbors.size(); i++) {
            if (graph[node1].neighbors[i].neighbor == node2) {
                if (graph[node1].neighbors[i].cost>0){
                    graph[node1].neighbors.erase(graph[node1].neighbors.begin() + i);
                    flag=-1;
                    break;
                    }
                else if (graph[node1].neighbors[i].cost==NO_PATH_COST){
                    cout << "Error: No path exist." << endl;
                    return;
                }
                break;
            }
        }

        for (size_t i = 0; i < graph[node2].neighbors.size(); i++) {
            if (graph[node2].neighbors[i].neighbor == node1) {
                    graph[node2].neighbors.erase(graph[node2].neighbors.begin() + i);
                    break;
            }
        }
        if (flag==-1)
            cout << "OK" << endl;
        else
            cout << "Error: There is no path between these nodes." << endl;

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

void calculateLSRP(int source) {
    int numNodes = graph.size();
    const int INF = numeric_limits<int>::max();

    vector<int> distance(numNodes, INF);
    distance[source] = 0;

    vector<bool> visited(numNodes, false);
    vector<int> parent(numNodes, -1);
    for (int step = 0; step < numNodes - 1; ++step) {
        int minDistance = INF;
        int minIndex = -1;
        for (int j = 0; j < numNodes; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }
        visited[minIndex] = true;
        for (const Edge& edge : graph[minIndex].neighbors) {
            int neighbor = edge.neighbor;
            int cost = edge.cost;
            if (!visited[neighbor] && distance[minIndex] != INF && distance[minIndex] + cost < distance[neighbor]) {
                distance[neighbor] = distance[minIndex] + cost;
                parent[neighbor] = minIndex;
            }
        }

        // Print the minimum cost in each step
        cout << "Step " << step + 1 << ": Minimum Cost from " << source << " to each node:" << endl;
        for (int i = 0; i < numNodes; ++i) {
            if (i != source) {
                int printedVal = (distance[i]==INF)?-1:distance[i];
                cout << "Node " << i << ": " << printedVal << endl;
            }
        }
        cout << endl;
    }

    // Print the shortest path and minimum cost at the end
    cout << "Shortest Path and Minimum Cost from " << source << " to each node:" << endl;
    for (int i = 0; i < numNodes; ++i) {
        if (i != source) {
            int currentNode = i;
            stack<int> shortestPath;
            while (currentNode != -1) {
                shortestPath.push(currentNode);
                currentNode = parent[currentNode];
            }

            cout << "Node " << i << ": ";
            while (!shortestPath.empty()) {
                cout << shortestPath.top() << " ";
                shortestPath.pop();
            }
            cout << "(Cost: " << distance[i] << ")" << endl;
        }
    }
}

void calculateDVRP(int source) {
    vector<int> distance(graphSize, INT8_MAX);
    vector<int> nextHop(graphSize, -1);
    distance[source] = 0;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].neighbors.size(); i++) {
            int v = graph[u].neighbors[i].neighbor;
            int cost = graph[u].neighbors[i].cost;

            if (distance[v] > distance[u] + cost) {
                distance[v] = distance[u] + cost;
                nextHop[v] = u;
                q.push(v);
            }
        }
    }
    cout << "DVRP for source:" << source <<"\n";
    cout << "Dest|NextHop|Dist| Shortest-Path\n"
        <<  "---------------------------------------------\n";
    for (int i = 0; i < graphSize; i++) {
        if (i != source) {
            cout << i << "   |   " << nextHop[i] << "   |  " << distance[i]<<" |  ";

            stack<int> path;
            int node = i;
            while (node != source) {
                path.push(node);
                node = nextHop[node];
            }
            path.push(source);

            cout << "[" ;
            while (!path.empty()) {
                cout << path.top();;
                path.pop();
                if(!path.empty())
                    cout<< "->";
            }
            cout << "]" <<endl;
        }
    }
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
    if (command==SET_MAX){
        graphSize= stoi(parsedCommand[1]);
        graph.resize(graphSize);
        for (int i = 0; i < graphSize; i++) {
            graph[i].id = i;
        }
    } else if (command==TOPOLOGY){
        for(int i=1;i<parsedCommand.size();i++){
            string currInp = parsedCommand[i];
            int node1, node2, cost;
            tie(node1, node2, cost) = parseTopologyCommand(currInp);

            if (node1==node2){
                cout << "wrong input. source and destination node are equal.\n";
                return 1;
            } else{
                addEdge(node1,node2,cost);
            }
        }
        cout << "OK\n";
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

    } else if (command==MODIFY) {
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

    } else if (command == LSRP) {
        if(parsedCommand.size()==2){
            int source = stoi(parsedCommand[1]);
            calculateLSRP(source);
            return 1;
        } else {
            for(int i=0;i<graph.size();i++){
                int currrSource = graph[i].id;
                calculateLSRP(currrSource);
                return 1;
            }
        }        
    } else if (command == DVRP) {
       if(parsedCommand.size()==2){
            int source = stoi(parsedCommand[1]);
            calculateDVRP(source);
            return 1;
        } else {
            for(int i=0;i<graph.size();i++){
                int curSource = graph[i].id;
                calculateDVRP(curSource);
            }
            return 1;
        }    
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
    return 1;
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