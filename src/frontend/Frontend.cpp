#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/ast/ast.h"
#include "scanner.h"

namespace MiniJavab {
namespace Frontend {

Core::Type* ConvertTypeNodeToType(AST::TypeNode* node) {
    if (node->IsIntegerType()) { return new Core::IntegerType(); }
    else if (node->IsVoidType()) { return new Core::VoidType(); }
    else if (node->IsStringType()) { return new Core::StringType(); }
    else if (node->IsBooleanType()) { return new Core::BooleanType(); }
    else if (node->IsObjectType()) {
        AST::ObjectTypeNode* typeNode = dynamic_cast<AST::ObjectTypeNode*>(node);
        return new Core::ObjectType(typeNode->ObjectType);
    }
    else if (node->IsArrayType()) {
        AST::ArrayTypeNode* typeNode = dynamic_cast<AST::ArrayTypeNode*>(node);
        return new Core::ArrayType(ConvertTypeNodeToType(typeNode->BaseType), typeNode->Dimensions);
    }

    assert(false && "AST TypeNode not recognized");
    return nullptr; // unreachable
}

AST::Node* ParseProgramFile(std::string fileName, std::ostream& errs) {
    Parser::ScanResult* result = Parser::ParseFileToAST(fileName);
    if (result->Result == nullptr) {
        // print errors to the error stream
        // TODO
        errs << "Encountered errors parsing: " << fileName << std::endl;
    }
    return result->Result;
}

ASTClassTable* LoadClassTableFromAST(AST::Node* tree) {
    assert(tree != nullptr && "Called LoadClassTableFromAST with a null argument");

    if (AST::ProgramNode* programNode = dynamic_cast<AST::ProgramNode*>(tree)) {
        ASTClassTable* table = new ASTClassTable();
        table->AddClass(programNode->MainClass);

        for (AST::ClassDeclNode* classDecl: programNode->Classes) {
            table->AddClass(classDecl);
        }
        table->Finalize();
        return table;
    }
    else {
        assert(false && "Invalid ast type");
        return nullptr; // unreachable
    }
}

}} // end namespace