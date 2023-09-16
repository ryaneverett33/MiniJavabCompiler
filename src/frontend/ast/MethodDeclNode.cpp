#include "minijavab/frontend/ast/MethodDeclNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

MethodDeclNode::MethodDeclNode(TypeNode* type, std::string name, std::vector<VarDeclNode*> parameters,
                                std::vector<VarDeclNode*> variables, std::vector<StatementNode*> statements, ExpNode* returnExp) :
                            Node(),
                            Type(type),
                            Name(name),
                            Parameters(parameters),
                            Variables(variables),
                            Statements(statements),
                            ReturnExp(returnExp) {}

void MethodDeclNode::Str(std::ostream& out) {
    out << "public ";
    if (dynamic_cast<MainMethodDeclNode*>(this) != nullptr) {
        out << "static ";
    }
    Type->Str(out);
    out << " " << Name << "(";
    for (int parameterIndex = 0; parameterIndex < Parameters.size(); parameterIndex++) {
        VarDeclNode* parameter = Parameters[parameterIndex];
        parameter->Type->Str(out);
        out << " " << parameter->Name;
        if ((parameterIndex + 1) < Parameters.size()) {
            out << ", ";
        }
    }
    out << ") {" << std::endl;
    if (Variables.size() > 0) {
        for (VarDeclNode* variable: Variables) {
            variable->Str(out);
            out << ";" << std::endl;
        }

        if (Statements.size() > 0) { out << std::endl; }
    }
    if (Statements.size() > 0) {
        for (StatementNode* statement: Statements) {
            statement->Dump(out);
        }
    }
    if (ReturnExp != nullptr) {
        out << "return ";
        ReturnExp->Str(out);
        out << ";" << std::endl;
    }
    out << "}";
}

}}} // end namespace