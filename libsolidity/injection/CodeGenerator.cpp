#include <libsolidity/injection/CodeGenerator.h>


using namespace std;
using namespace langutil;
using namespace dev::solidity;


ASTPointer<ModifierDefinition> CodeGenerator::generateModifierDefinition(Modifier _modifier) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(
            CharStream(_modifier.toString(), _modifier.Name()));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ModifierDefinition> modifier = m_parser.parseModifierDefinition();
    m_parser.setScanner(m_scanner);
    return modifier;
}


ASTPointer<ModifierInvocation> CodeGenerator::generateModifierInvocation(string _modifierName) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(_modifierName, _modifierName));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ModifierInvocation> modifier_invocation = m_parser.parseModifierInvocation();
    m_parser.setScanner(m_scanner);
    return modifier_invocation;
}


ASTPointer<VariableDeclaration> CodeGenerator::generateGlobalVariableDeclaration(VarDeclaration _var) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(CharStream(_var.toString(), _var.Name()));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<VariableDeclaration> var_declaration = m_parser.parseGlobalVariableDeclaration();
    m_parser.setScanner(m_scanner);
    return var_declaration;
}

ASTPointer<Statement> CodeGenerator::generateInitStatement(InitStatement _statement) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(
            CharStream(_statement.toString(), _statement.Name()));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ASTString> docString;
    ASTPointer<Statement> var_init = m_parser.parseSimpleStatement(docString);
    m_parser.setScanner(m_scanner);
    return var_init;
}

ASTPointer<ASTNode> CodeGenerator::generateFunctionDefinition(Function _func) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(
            CharStream(_func.toString(), _func.Name()));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<ASTNode> func = m_parser.parseFunctionDefinitionOrFunctionTypeStateVariable();
    m_parser.setScanner(m_scanner);
    return func;
}

ASTPointer<EventDefinition> CodeGenerator::generateEventDefinition(Event _event) {
    shared_ptr<langutil::Scanner> scanner = make_shared<Scanner>(
            CharStream(_event.toString(), _event.Name()));
    shared_ptr<langutil::Scanner> m_scanner = m_parser.getScanner();
    m_parser.setScanner(scanner);
    ASTPointer<EventDefinition> event = m_parser.parseEventDefinition();
    m_parser.setScanner(m_scanner);
    return event;
}
