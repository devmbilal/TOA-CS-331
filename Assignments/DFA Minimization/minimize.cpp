#include<iostream>
using namespace std;
#include<fstream>
#include <map>
#include<list>

class State
{
private:
    string name;
    bool isInitial;
    bool isAccepting;
    map <char, string> transitions;
public:
    State(string name, bool isInitial, bool isAccepting , map <char, string> transitions)
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
 DFA(/* args */);

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
 



};






