#pragma once

#include <string>
#include <vector>


using namespace std;

namespace uds {
    class Element {
    protected:
        string m_elementName;
        string m_name;

    public:
        Element(string const& elementName, string const& name):
            m_elementName(elementName),
            m_name(name) {}

        string ElementName() {
            return m_elementName;
        }

        string Name() {
            return m_name;
        }

//        virtual string toString() = 0;
    };

    class VarDeclaration: public Element {
    private:
        string m_typeName;
        string m_value;

    public:
        VarDeclaration(
            string const& typeName,
            string const& name,
            string const& value = ""
        ):
            Element("VariableDeclaration", name),
            m_typeName(typeName),
            m_value(value) {}

        string toString();
    };

    class InitStatement: public Element {
    private:
        string m_statement;

    public:
        InitStatement(
            string statement,
            string name
        ):
            Element("SimpleStatement", name),
            m_statement(statement){}

        string toString();
    };

    class Event: public  Element {
    private:
        vector<string> m_params;
    public:
        Event(
            string const& name,
            vector<string> params
        ):
            Element("Event", name),
            m_params(params) {}

        string toString();
    };

    class Modifier: public Element {
    private:
        string m_block;

    public:
        Modifier(
            string const& name,
            string const& block
        ):
            Element("Modifier", name),
            m_block(block) {}

        string toString();
    };

    class Function: public Element {
    private:
        string m_block;
        vector<string> m_modifierNames;
        vector<string> m_params;
        vector<string> m_returns;

    public:
        Function(
            string const& name,
            string const& block,
            vector<string> modifiers,
            vector<string> params,
            vector<string> returns
        ):
            Element("Modifier", name),
            m_block(block),
            m_modifierNames(modifiers),
            m_params(params),
            m_returns(returns) {}

        string toString();
        void addModifier(string modifierName);
        void addParam(string param);
        void addReturn(string ret);
    };


}