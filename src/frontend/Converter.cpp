#include "minijavab/frontend/Converter.h"

#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/ast/Type.h"

#include "minijavab/core/ir/Module.h"
#include "minijavab/core/ir/IntegerConstant.h"

using namespace MiniJavab::Core;
using namespace MiniJavab::Frontend;

namespace MiniJavab {
namespace Frontend {

ASTConverter::ASTConverter(ASTClassTable* table, std::string fileName)
    : _classTable(table) {
    _module = new Core::IR::Module(fileName);
}

IR::Type* ASTConverter::ResolveASTType(AST::Type* type) {
    switch (type->GetKind()) {
        case AST::TypeKind::Integer:
            return new IR::IntegerType(32);
        case AST::TypeKind::Void:
            return new IR::VoidType();
        case AST::TypeKind::String:
            return new IR::VectorType(new IR::IntegerType(8));
        case AST::TypeKind::Boolean:
            return new IR::BooleanType();
        case AST::TypeKind::Object: {
            AST::ObjectType* objectType = static_cast<AST::ObjectType*>(type);
            return _classTypeTable.find(objectType->TypeName)->second;
        }
        case AST::TypeKind::Method: {
            AST::MethodType* methodType = static_cast<AST::MethodType*>(type);
            std::vector<IR::Type*> parameterTypes;
            for (AST::Type* parameterType : methodType->ParameterTypes) {
                parameterTypes.push_back(ResolveASTType(parameterType));
            }

            return new IR::FunctionType(ResolveASTType(methodType->ReturnType), parameterTypes);
        }
        case AST::TypeKind::Array: {
            AST::ArrayType* arrayType = static_cast<AST::ArrayType*>(type);
            IR::Type* baseType = ResolveASTType(arrayType->BaseType);
            
            // Create an n-dimensional vector of basetype
            IR::Type* resultantType = new IR::VectorType(baseType);
            for (size_t i = arrayType->Dimensions; i > 1; i--) {
                resultantType = new IR::VectorType(resultantType);
            }
            return resultantType;
        }
        default:
            assert(false && "Unknown Type Kind!");
    }
}

void ASTConverter::CreateMetadataTypes() {
    // Create %method_type_t = type { vector<i8>, vector<vector<i8>> }
    IR::StructType* methodTypeType = new IR::StructType("method_type_t", {
        new IR::VectorType(new IR::IntegerType(8)),
        new IR::VectorType(new IR::VectorType(new IR::IntegerType(8)))
    });

    // Create %variable_t = type { vector<i8>, vector<i8>, i32 }
    IR::StructType* variableType = new IR::StructType("variable_t", {
        new IR::VectorType(new IR::IntegerType(8)),
        new IR::VectorType(new IR::IntegerType(8)),
        new IR::IntegerType(32)
    });

    // Create %method_t = type { vector<i8>, %method_type_t*, bool, void* }
    IR::StructType* methodType = new IR::StructType("method_t", {
        new IR::VectorType(new IR::IntegerType(8)),
        new IR::PointerType(methodTypeType),
        new IR::BooleanType(),
        new IR::PointerType(new IR::VoidType())
    });

    // Create %class_t = type { vector<i32>, %class_t*, vector<%variable_t>, vector<%method_t> }
    IR::StructType* classType = new IR::StructType("class_t", {
        new IR::VectorType(new IR::IntegerType(8)),
        new IR::PointerType(nullptr), /* placeholder for circular type */
        new IR::VectorType(variableType),
        new IR::VectorType(methodType)
    });
    static_cast<IR::PointerType*>(classType->ContainedTypes[1])->ElementType = classType;

    // Add types to module
    _module->AddStructType(methodTypeType);
    _module->AddStructType(variableType);
    _module->AddStructType(methodType);
    _module->AddStructType(classType);
}

IR::GlobalVariable* ASTConverter::CreateMetadataMethodType(ASTClass* parentClass, ASTMethod* method) {
    // Resolve types
    IR::Type* returnType = ResolveASTType(method->ReturnType);
    std::vector<IR::Type*> parameterTypes;
    for (auto& [name, parameter] : method->Parameters) {
        parameterTypes.push_back(ResolveASTType(parameter->Type));
    }

    // create initializer
    IR::IntegerConstant* initializer = new IR::IntegerConstant(returnType, 69);

    // create global variable
    std::string name = "MJAVA_METHOD_" + parentClass->Name + "_" + method->Name + "_TYPE";
    IR::GlobalVariable* variable = new IR::GlobalVariable(name, initializer);
    _module->AddGlobalVariable(variable);

    return variable;
}

void ASTConverter::CreateClassTypes() {
    // First pass, create all class types as empty
    for (auto& [name, definition] : _classTable->Classes) {
        IR::StructType* classType = new IR::StructType(name, {});
        _classTypeTable.insert(std::make_pair(name, classType));
        _module->AddStructType(classType);
    }

    // Second pass, fill out newly created class types
    for (auto& [name, definition] : _classTable->Classes) {
        IR::StructType* classType = _classTypeTable.find(name)->second;

        std::vector<IR::Type*> variableTypes;
        for (auto& [_, variableDefinition] : definition->Variables) {
            variableTypes.push_back(ResolveASTType(variableDefinition->Type));
        }
        classType->ContainedTypes = variableTypes;
    }
}

void ASTConverter::CreateClassMetadata() {
    CreateMetadataTypes();
    
    for (auto& [className, classDefinition] : _classTable->Classes) {
        for (auto& [methodName, methodDefinition] : classDefinition->Methods) {
            IR::GlobalVariable* methodType = CreateMetadataMethodType(classDefinition, methodDefinition);
        }
    }
}

Core::IR::Module* ASTConverter::Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName) {
    ASTConverter converter(table, fileName);
    converter.CreateClassTypes();
    converter.CreateClassMetadata();
    
    return converter._module;
}

}} // end namespace