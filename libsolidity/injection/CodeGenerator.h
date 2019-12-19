#include <libsolidity/ast/AST.h>
#include <libsolidity/parsing/Parser.h>

using namespace dev::solidity;

class CodeGenerator {
private:
    Parser m_parser;
public:
    CodeGenerator(Parser const& _parser) :
            m_parser(_parser) {}

    ASTPointer<ModifierDefinition> generateModifierDefinition(Modifier _modifier);

    ASTPointer<ModifierInvocation> generateModifierInvocation(string _modifierName);

    ASTPointer<VariableDeclaration> generateGlobalVariableDeclaration(VarDeclaration _var);

    ASTPointer<Statement> generateInitStatement(InitStatement _statement);

    ASTPointer<EventDefinition> generateEventDefinition(Event _event);

    ASTPointer<dev::solidity::ASTNode> generateFunctionDefinition(Function _func);
};

