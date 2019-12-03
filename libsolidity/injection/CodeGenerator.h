#include <libsolidity/ast/AST.h>

# include <libsolidity/parsing/Parser.h>


namespace dev
{
namespace solidity
{

class CodeGenerator
{
private:
    Parser m_parser;
public:
    CodeGenerator(Parser parser);
    ~CodeGenerator();

    ASTPointer<ModifierDefinition> generateModifier();
    ASTPointer<ModifierInvocation> generateModifierInvocation();
    ASTPointer<ParameterList> generateParameterList();
    ASTPointer<VariableDeclaration> generateGlobalVariableDeclaration();
    ASTPointer<Statement> generateStatement();
};


}
}
