#include<iostream>
using namespace std;
#include<fstream>
#include<map>
#include<list>
#include<sstream>
#include<vector>

class State
{
private:
    string name;
    bool isInitial;
    bool isAccepting;
    map <string, string> transitions;
public:
    State(string name, bool isInitial, bool isAccepting , map <string,string> transitions)
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

    string getName()
    {
        return name;
    }

    map<string,string> getTransitions()
    {
        return transitions;
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

 list<State> getNonAcceptingStates(){
    list<State> nonAcceptingStates;
    for (list<State>::iterator i = states.begin(); i != states.end(); i++)
    {
        if( !i->isAcceptingState()){
            nonAcceptingStates.push_back(*i);
        }
    }
    return nonAcceptingStates;
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
    vector<string> symbols;
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
                symbols.push_back(linePart);
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
        map<string,string> transitionMap;
        for (int i = 0; i < symbols.size(); i++) {
            transitionMap[symbols[i]] = transitions[i+1];
        }

        // State Object
        State state(transitions[0], isInitial, isAccepting,transitionMap);

        // Add the State object to the states list
        states.push_back(state);

    }
}

 void writeToFile(string fileName)
{
        ofstream file(fileName);
        for (State& state : states)
        {
            file << (state.isInitialState() ? "i " : "") << state.getName() << (state.isAcceptingState() ? "*" : "") << ", ";
            for (auto& transition : state.getTransitions())
            {
                file << transition.second << ", ";
            }
            file << "\n";
        }
        file.close();
}

void minimize(){
    list<list<State>> partitions;
    list<State> acceptingStates = getAcceptingStates();
    list<State> nonAcceptingStates = getNonAcceptingStates();

    partitions.push_back(acceptingStates);
    partitions.push_back(nonAcceptingStates);
    
    bool changed;
    do
    {
        changed = false;
        list<list<State>> newPartitions;

        for (list<State>& partition : partitions)
        {
            map<string, list<list<State>::iterator>> transitionPartitions;

            for (auto it = partition.begin(); it != partition.end(); ++it)
            {
                for (auto& transition : it->getTransitions())
                {
                    transitionPartitions[transition.second].push_back(it);
                }
            }

            for (auto& transitionPartition : transitionPartitions)
            {
                if (transitionPartition.second.size() < partition.size())
                {
                    list<State> newPartition;
                    for (auto it : transitionPartition.second)
                    {
                        newPartition.push_back(*it);
                        partition.erase(it);
                    }
                    newPartitions.push_back(newPartition);
                    changed = true;
                }
            }
        }

        partitions.insert(partitions.end(), newPartitions.begin(), newPartitions.end());
    } while (changed);

     states.clear();
    for (list<State>& partition : partitions)
    {
        string name;
        bool isInitial = false;
        bool isAccepting = false;
        map<string, string> transitions;

        for (State& state : partition)
        {
            name += state.getName();
            isInitial |= state.isInitialState();
            isAccepting |= state.isAcceptingState();
            transitions = state.getTransitions();  // Assumes all states in the partition have the same transitions.
        }

        addState(State(name, isInitial, isAccepting, transitions));
    }
}

};



int main()
{
    DFA dfa;
    dfa.readFromFile("dfa.txt");
    dfa.minimize();
    dfa.writeToFile("minimizedDFA.txt");
    return 0;
}


