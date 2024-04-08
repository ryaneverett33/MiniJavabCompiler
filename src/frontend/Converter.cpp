#include "minijavab/frontend/Converter.h"

#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/ast/Type.h"
#include "minijavab/frontend/InstructionLowering.h"

#include "minijavab/core/ir/Module.h"
#include "minijavab/core/ir/IntegerConstant.h"
#include "minijavab/core/ir/VectorConstant.h"
#include "minijavab/core/ir/StringConstant.h"
#include "minijavab/core/ir/StructConstant.h"

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
            // todo this isn't used?
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
    static_cast<IR::PointerType*>(classType->ElementTypes[1])->ElementType = classType;

    // Add types to module
    _module->AddStructType(methodTypeType);
    _module->AddStructType(variableType);
    _module->AddStructType(methodType);
    _module->AddStructType(classType);
}

IR::GlobalVariable* ASTConverter::CreateMetadataMethod(ASTClass* parentClass, ASTMethod* method) {
    // Resolve types
    std::vector<std::string> parameterTypeNames;
    for (auto& [name, parameter] : method->Parameters) {
        std::cout << "Parameter type: " << parameter->Type->GetName() << "\n";
        parameterTypeNames.push_back(parameter->Type->GetName());
    }

    // create vector constant from parameterTypeNames
    std::vector<IR::Constant*> parameterTypes;
    for (std::string parameterTypeName : parameterTypeNames) {
        parameterTypes.push_back(new IR::StringConstant(parameterTypeName));
    }

    // create initializer
    //IR::IntegerConstant* initializer = new IR::IntegerConstant(returnType, 69);
    IR::Type* methodTypeT = _module->GetStructTypeByName("method_type_t");
    IR::VectorConstant* parameterTypesConstant = new IR::VectorConstant(new IR::VectorType(IR::StringType()), parameterTypes);
    IR::StringConstant* returnTypeConstant = new IR::StringConstant(method->ReturnType->GetName());
    IR::StructConstant* initializer = new IR::StructConstant(methodTypeT, {returnTypeConstant, parameterTypesConstant});

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
        classType->ElementTypes = variableTypes;
    }
}

void ASTConverter::CreateClassMetadata() {
    CreateMetadataTypes();

    // known types

    IR::Type* classTType = _module->GetStructTypeByName("class_t");
    IR::Type* variableTType = _module->GetStructTypeByName("variable_t");
    IR::Type* methodTType = _module->GetStructTypeByName("method_t");
    IR::Type* methodTypeTType = _module->GetStructTypeByName("method_type_t");

    // vectorized types

    /// vector<%variable_t>
    IR::Type* vectorVariableType = new IR::VectorType(variableTType);
    /// vector<%method_t>
    IR::Type* vectorMethodType = new IR::VectorType(methodTType);

    // pointer types

    /// %class_t*
    IR::Type* classPointerType = new IR::PointerType(classTType);
    /// %method_type_t*
    IR::Type* methodTypePointerType = new IR::PointerType(methodTypeTType);
    /// void*
    IR::Type* voidPointerType = new IR::PointerType(new IR::VoidType());

    // helper types

    IR::Type* structOffsetType = new IR::IntegerType(32, false);
    
    for (auto& [className, classDefinition] : _classTable->Classes) {
        std::vector<IR::Constant*> methodTypes;
        std::vector<IR::Constant*> variableTypes;

        // Fill out variable metadata
        uint32_t structOffset = 0;
        for (auto& [variableName, variableDefinition] : classDefinition->Variables) {
            variableTypes.push_back(new IR::StructConstant(variableTType, {
                new IR::StringConstant(variableName),
                new IR::StringConstant(variableDefinition->Type->GetName()),
                new IR::IntegerConstant(structOffsetType, new IR::Immediate(structOffsetType, structOffset))
            }));
            structOffset += 1;
        }
        
        // Fill out method metadata
        for (auto& [methodName, methodDefinition] : classDefinition->Methods) {
            // Create the method_type_t variable
            IR::GlobalVariable* methodType = CreateMetadataMethod(classDefinition, methodDefinition);
            methodTypes.push_back(new IR::StructConstant(methodTType, {
                new IR::StringConstant(methodName),
                IR::Constant::GetNull(methodTypePointerType),
                new IR::BooleanConstant(false),
                IR::Constant::GetNull(voidPointerType)
            }));
        }

        // Create the variable initializer
        IR::StructConstant* classInitializer = new IR::StructConstant(classTType, {
            new IR::StringConstant(className),
            IR::Constant::GetNull(classPointerType),
            new IR::VectorConstant(vectorVariableType, variableTypes),
            new IR::VectorConstant(vectorMethodType, methodTypes)
        });

        // Create and add the new global variable
        IR::GlobalVariable* classVariable = new IR::GlobalVariable("MJAVA_CLASS_" + className, classInitializer);
        _module->AddGlobalVariable(classVariable);
    }
}

void ASTConverter::CreateFunctionSignatures() {
    for (auto& [className, classDefinition] : _classTable->Classes) {
        for (auto& [methodName, methodDefinition] : classDefinition->Methods) {
            std::string functionName = className + "_" + methodName;

            // Resolve parameter types
            std::vector<IR::Type*> parameterTypes;
            std::vector<std::string> parameterNames;
            parameterTypes.reserve(methodDefinition->Parameters.size());
            parameterNames.reserve(methodDefinition->Parameters.size());
            for (auto& [parameterName, parameterDefinition] : methodDefinition->Parameters) {
                parameterTypes.push_back(ResolveASTType(parameterDefinition->Type));
                parameterNames.push_back(parameterName);
            }

            // Create function type
            IR::FunctionType* functionType = new IR::FunctionType(ResolveASTType(methodDefinition->ReturnType), parameterTypes);

            // Create function and add it to the module
            IR::Function* function = new IR::Function(functionName, functionType);
            _module->AddFunction(function);

            // Assign parameter names
            for (IR::Parameter* functionParameter : function->GetParameters()) {
                functionParameter->Name = parameterNames[functionParameter->GetIndex()];
            }
        }
    }
}

void ASTConverter::LowerFunctions() {
    InstructionLowering* instructionLowering = new InstructionLowering(this);

    for (auto& [className, classDefinition] : _classTable->Classes) {
        for (auto& [methodName, methodDefinition] : classDefinition->Methods) {
            std::string functionName = className + "_" + methodName;

            IR::Function* function = _module->GetFunctionByName(functionName);
            instructionLowering->LowerFunction(methodDefinition, function);
        }
    }
}

Core::IR::Module* ASTConverter::Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName) {
    ASTConverter converter(table, fileName);
    converter.CreateClassTypes();
    converter.CreateFunctionSignatures();
    converter.LowerFunctions();

    // Create metadata last after all types and functions have been created
    converter.CreateClassMetadata();
    
    return converter._module;
}

}} // end namespace