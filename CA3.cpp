#include <iostream>
#include <sstream>
#include <vector>

#define SEPERATOR ' '

using namespace std;


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
    for (int i=0;i<parsedCommand.size();i++){
        cout << parsedCommand[i] << "\n";
    }
    cout << "\n";
    return 1;
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