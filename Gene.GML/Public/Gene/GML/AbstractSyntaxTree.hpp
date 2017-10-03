#pragma once

#include <vector>
#include <string>

namespace Gene {
    namespace GML {
        class ASTNode {};
        class ExpressionNode {};

        class IntegerNode : public ExpressionNode
        {
        public:
            int Value;
            IntegerNode(int value): Value(value) {}
        };

        class ArithmeticNode : public ExpressionNode
        {
        public:
            ExpressionNode *Left;
            ExpressionNode *Right;
            Token OperationToken;

            ArithmeticNode(ExpressionNode *left, ExpressionNode *right, Token op):
                Left(left), Right(right), OperationToken(op){}
        };

    }
}
