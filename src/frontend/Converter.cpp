#include "minijavab/frontend/Converter.h"


#include "minijavab/frontend/ast/ast.h"
#include "minijavab/core/ir/Module.h"
#include "minijavab/core/ir/Type.h"

namespace MiniJavab {
namespace Frontend {

ASTConverter::ASTConverter(ASTClassTable* table, std::string fileName)
    : _classTable(table) {
    _module = new Core::IR::Module(fileName);
}

void ASTConverter::createMetadataTypes() {
    using namespace MiniJavab::Core::IR;
    // Create %method_type_t = type { vector<i8>, vector<vector<i8>> }
    StructType* methodTypeType = new StructType("method_type_t", {
        new VectorType(new IntegerType(8)),
        new VectorType(new VectorType(new IntegerType(8)))
    });

    // Create %variable_t = type { vector<i8>, vector<i8>, i32 }
    StructType* variableType = new StructType("variable_t", {
        new VectorType(new IntegerType(8)),
        new VectorType(new IntegerType(8)),
        new IntegerType(32)
    });

    // Create %method_t = type { vector<i8>, %method_type_t*, bool, void* }
    StructType* methodType = new StructType("method_t", {
        new VectorType(new IntegerType(8)),
        new PointerType(methodTypeType),
        new BooleanType(),
        new PointerType(new VoidType())
    });

    // Create %class_t = type { vector<i32>, %class_t*, vector<%variable_t>, vector<%method_t> }
    StructType* classType = new StructType("class_t", {
        new VectorType(new IntegerType(8)),
        new PointerType(nullptr), /* placeholder for circular type */
        new VectorType(variableType),
        new VectorType(methodType)
    });
    static_cast<PointerType*>(classType->ContainedTypes[1])->ElementType = classType;

    // Add types to module
    _module->AddStructType(methodTypeType);
    _module->AddStructType(variableType);
    _module->AddStructType(methodType);
    _module->AddStructType(classType);
}

void ASTConverter::createClassMetadata() {
    createMetadataTypes();
    for (auto& [name, definition] : _classTable->Classes) {
        // Create the class type
        //_module->AddType();
    }
}

Core::IR::Module* ASTConverter::Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName) {
    ASTConverter converter(table, fileName);
    converter.createClassMetadata();
    
    return converter._module;
}

}} // end namespace