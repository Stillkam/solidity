//
// Created by Jay Ele on 2019/12/9.
//

#include <libsolidity/injection/Element.h>

#include <boost/algorithm/string/join.hpp>
#include <vector>

using namespace uds;

string VarDeclaration::toString() {
    vector<string> components;
    components.push_back(this->m_typeName);
    components.push_back(this->m_name);
    if (this->m_value.size() > 0) {
        components.push_back("=");
        components.push_back(this->m_value);
    }
    components.push_back(";");
    return boost::algorithm::join(components, " ");
}

string InitStatement::toString() {
    return m_statement;
}

string Event::toString() {
    vector<string> components;
    components.push_back("event");
    string arguments = "(" + boost::algorithm::join(this->m_params, ", ") + ")";
    components.push_back(this->m_name + arguments);
    components.push_back(";");
    return boost::algorithm::join(components, " ");
}

string Modifier::toString() {
    vector<string> components;
    components.push_back("modifier");
    components.push_back(this->m_name);
    components.push_back("{\n");
    components.push_back(this->m_block);
    components.push_back("\n}");
    return boost::algorithm::join(components, " ");
}

string Function::toString() {
    vector<string> components;
    components.push_back("function");
    string arguments = "(" + boost::algorithm::join(this->m_params, ", ") + ")";
    components.push_back(this->m_name + arguments);
    components.push_back("external");
    for (string modifier: this->m_modifierNames)
        components.push_back(modifier);
    if (this->m_returns.size() > 0) {

        components.push_back("returns");
        string returns = boost::algorithm::join(this->m_returns, ", ");
        components.push_back("(" + returns + ")");
    }
    components.push_back("{\n");
    components.push_back(this->m_block);
    components.push_back("\n}");
    return boost::algorithm::join(components, " ");
}

void Function::addModifier(string modifierName) {
    this->m_modifierNames.push_back(modifierName);
}

void Function::addParam(string param) {
    this->m_params.push_back(param);
}

void Function::addReturn(string ret) {
    this->m_returns.push_back(ret);
}






