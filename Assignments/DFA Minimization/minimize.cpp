#include<iostream>
using namespace std;
#include<fstream>
#include <map>
#include<list>
#include <sstream>
#include <vector>

class State
{
private:
    string name;
    bool isInitial;
    bool isAccepting;
    map <char, string> transitions;
public:
    State(string name, bool isInitial, bool isAccepting , map <char,string> transitions)
    {
        this->name = name;
        this->isInitial = isInitial;
        this->isAccepting = isAccepting;
        this->transitions = transitions;
    }
    bool operator==(const State& s) const
    {
        return name == s.name;
    }
    bool isInitialState()
    {
        return isInitial;
    }
    bool isAcceptingState()
    {
        return isAccepting;
    }
};

class DFA
{
private:
        list<State> states;
public:

 void addState(State state)
 { 
    for (list<State>::iterator i = states.begin(); i != states.end(); i++)
    {
        if( *i == state){
            cout<<"State already exists";
            return;
        }
    }
    states.push_back(state);
 }
 State getInitialState()
 {
     for (list<State>::iterator i = states.begin(); i != states.end(); i++)
    {
        if( i->isInitialState()){
            return *i;
        }
    }
    cout<<"No initial state found";
 }
 
 list<State> getAcceptingStates()
 {
     list<State> acceptingStates;
     for (list<State>::iterator i = states.begin(); i != states.end(); i++)
    {
        if( i->isAcceptingState()){
            acceptingStates.push_back(*i);
        }
    }
    return acceptingStates;
 }

 void readFromFile(string fileName)
{
    // Check if file exists
    ifstream file;
    file.open(fileName);
    if (!file)
    {
        cout << "File not Found";
        return;
    }
    string line;
    int lineNumber = 0;
    vector<char> symbols;
    // Read file line by line
    while (getline(file,line))
    {
        lineNumber++;
        //Header line 
        if (lineNumber == 1)
        {
            istringstream stringStream(line);
            string linePart;
            getline(stringStream, linePart,',');
            while(getline(stringStream, linePart,','))
            {
                symbols.push_back(linePart[0]);
            } 
            continue;      
        }

      // Read the states
      bool isInitial = false;
      bool isAccepting = false;

        if (line[0] == 'i') {
            isInitial = true;
            line = line.substr(2);  
        }

        if (line[0] == '*') {
            isAccepting = true;
            line = line.substr(2); 
        }

        istringstream stringStream(line);
        string linePart;
        vector<string> transitions;

        while(getline(stringStream, linePart, ',')) {
            transitions.push_back(linePart);
        }
        
      

       // Create a map for the transitions
        map<char,string> transitionMap;
        for (int i = 0; i < symbols.size(); i++) {
            transitionMap[symbols[i]] = transitions[i+1];
        }

        // State Object
        State state(transitions[0], isInitial, isAccepting,transitionMap);

        // Add the State object to the states list
        states.push_back(state);

    }
}
  

};





