#include <libsolidity/injection/CodeGenerator.h>
#include <libsolidity/injection/Defense.h>

#include <libsolidity/parsing/Parser.h>


using namespace std;
using namespace langutil;

namespace dev
{
namespace solidity
{

CodeGenerator::CodeGenerator(Parser parser):
    m_parser(parser) {}

ASTPointer<ModifierDefinition> CodeGenerator::generateModifier()
{
    defense::Modifier m_modifier = defense::Modifier();
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(m_modifier.getModifier(), "testModifier"));

    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ModifierDefinition> modifier = m_parser.parseModifierDefinition();
    m_parser.setScanner(m_scanner);
    return modifier;
}


ASTPointer<ModifierInvocation> CodeGenerator::generateModifierInvocation()
{
    defense::Modifier m_modifier = defense::Modifier();
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(m_modifier.getName(), "testModifierInvocation"));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ModifierInvocation> modifier_invocation = m_parser.parseModifierInvocation();
    m_parser.setScanner(m_scanner);
    return modifier_invocation;
}


ASTPointer<VariableDeclaration> CodeGenerator::generateGlobalVariableDeclaration()
{
    defense::Statement statement = defense::Statement();
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(statement.getDeclarStatement(), "declareStatement"));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<VariableDeclaration> var_declaration = m_parser.parseGlobalVariableDeclaration();
    m_parser.setScanner(m_scanner);
    return var_declaration;
}

ASTPointer<Statement> CodeGenerator::generateStatement()
{
    defense::Statement statement = defense::Statement();
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(statement.getInitStatement(), "initStatement"));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<Statement> var_init = m_parser.parseStatement();
    m_parser.setScanner(m_scanner);
    return var_init;
}

}
}
