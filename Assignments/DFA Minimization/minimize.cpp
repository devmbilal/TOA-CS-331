#include<iostream>
using namespace std;
#include<fstream>
#include <map>

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
};




