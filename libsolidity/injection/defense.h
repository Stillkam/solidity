//
// Created by Jay Ele on 2019/12/12.
//

#include <vector>
#include <map>
#include <string>

#include <libsolidity/injection/Element.h>

using namespace std;
using namespace uds;

class Defense {
public:
    map<string, VarDeclaration const*> varDeclarations;
    vector<InitStatement> initStatements;

    map<string, Modifier const*> modifiers;
    map<string, Event const*> events;
    map<string, Function const*> functions;

    string securityController;
    int securityLevel;


    Defense(string SEController, int SELevel):
        securityController(SEController),
        securityLevel(SELevel) {}

    void prepareVarDeclarations();
    void prepareInitStatements();
    void prepareModifiers();
    void prepareEvents();
    void prepareFunctions(bool super=false);
    void resetFunctions();
};