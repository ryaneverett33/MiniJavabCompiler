#include "minijavab/frontend/InstructionLowering.h"

#include <cassert>

#include "minijavab/core/ir/Immediate.h"

#include "minijavab/frontend/PrimitiveTypes.h"

namespace MiniJavab {
namespace Frontend {
namespace ImmediateFolder {

Core::IR::Immediate* ConvertLiteral(AST::LiteralExpNode* literal) {
    if (literal->IsBooleanLiteral()) {
        return new Core::IR::Immediate(PrimitiveTypes::Boolean(), static_cast<AST::BooleanLiteralExpNode*>(literal)->Value);
    }
    else {
        return new Core::IR::Immediate(PrimitiveTypes::Int(), static_cast<AST::IntegerLiteralExpNode*>(literal)->Value);
    }
}

bool CanFold(AST::ExpNode* expression) {
    if (expression->IsBinaryExpression()) {
        AST::BinaryExpNode* binaryExpression = static_cast<AST::BinaryExpNode*>(expression);

        return binaryExpression->LeftSide->IsLiteralExpression() && binaryExpression->RightSide->IsLiteralExpression();
    }
    else if (expression->IsUnaryExpression()) {
        AST::UnaryExpNode* unaryExpression = static_cast<AST::UnaryExpNode*>(expression);

        return unaryExpression->Expression->IsLiteralExpression();
    }
    return false;
}

Core::IR::Immediate* Fold(AST::BinaryExpNode* expression) {
    Core::IR::Immediate* leftHandSide = ConvertLiteral(static_cast<AST::LiteralExpNode*>(expression->LeftSide));
    Core::IR::Immediate* rightHandSide = ConvertLiteral(static_cast<AST::LiteralExpNode*>(expression->RightSide));

    if (leftHandSide->ValueType->IsBooleanType()) {
        switch (expression->Operator) {
            case AST::OperatorType::BooleanAnd:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetBoolean() && rightHandSide->GetBoolean()));
            case AST::OperatorType::BooleanOr:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetBoolean() || rightHandSide->GetBoolean()));
            case AST::OperatorType::NotEqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetBoolean() != rightHandSide->GetBoolean()));
            case AST::OperatorType::EqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetBoolean() == rightHandSide->GetBoolean()));
            default:
                assert(false && "Invalid expression type");
        }
    }
    else {
        switch (expression->Operator) {
            case AST::OperatorType::EqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() == rightHandSide->GetI32()));
            case AST::OperatorType::NotEqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() != rightHandSide->GetI32()));
            case AST::OperatorType::LessThanEqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() <= rightHandSide->GetI32()));
            case AST::OperatorType::GreaterThanEqualTo:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() >= rightHandSide->GetI32()));
            case AST::OperatorType::LessThan:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() < rightHandSide->GetI32()));
            case AST::OperatorType::GreaterThan:
                return new Core::IR::Immediate(PrimitiveTypes::Boolean(), (leftHandSide->GetI32() > rightHandSide->GetI32()));
            case AST::OperatorType::Add:
                return new Core::IR::Immediate(PrimitiveTypes::Int(), (leftHandSide->GetI32() + rightHandSide->GetI32()));
            case AST::OperatorType::Subtract:
                return new Core::IR::Immediate(PrimitiveTypes::Int(), (leftHandSide->GetI32() - rightHandSide->GetI32()));
            case AST::OperatorType::Multiply:
                return new Core::IR::Immediate(PrimitiveTypes::Int(), (leftHandSide->GetI32() * rightHandSide->GetI32()));
            case AST::OperatorType::Divide:
                return new Core::IR::Immediate(PrimitiveTypes::Int(), (leftHandSide->GetI32() / rightHandSide->GetI32()));
            default:
                assert(false && "Invalid expression type");
        }
    }
}

Core::IR::Immediate* Fold(AST::UnaryExpNode* expression) {
    Core::IR::Immediate* immediate = ConvertLiteral(static_cast<AST::LiteralExpNode*>(expression->Expression));

    switch (expression->Operator) {
        case AST::OperatorType::Add:
            return immediate;
        case AST::OperatorType::Subtract: {
            immediate->Set(immediate->GetI32() * -1);
            return immediate;
        }
        case AST::OperatorType::BooleanNot: {
            immediate->Set(!immediate->GetBoolean());
            return immediate;
        }
        default:
            assert(false && "Invalid expression type");
    }
}

Core::IR::Immediate* Fold(AST::ExpNode* expression) {
    if (expression->IsBinaryExpression()) {
        return Fold(static_cast<AST::BinaryExpNode*>(expression));
    }
    else if (expression->IsUnaryExpression()) {
        return Fold(static_cast<AST::UnaryExpNode*>(expression));
    }
    assert(false && "unrecognized fold type");
}


}}} // end namespace