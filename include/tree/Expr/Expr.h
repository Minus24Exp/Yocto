#ifndef EXPR_H
#define EXPR_H

#include "tree/Node.h"

namespace jc::tree {
    struct Expr;
    using expr_ptr = std::shared_ptr<Expr>;
    using ExprList = std::vector<expr_ptr>;

    enum class ExprType {
        Grouping,
        Literal,
        Id,
        Infix,
        Prefix,
        Assign,
        Set,
        Get,
        Call,
        MethodCall,
        If,
        GetItem,
        SetItem,
        List,
        Dict,
        Spread,
    };

    struct Expr : Node {
        Expr(const Position & pos, ExprType type) : Node(pos), type(type) {}

        void accept(BaseVisitor & visitor) override = 0;

        ExprType type;
    };
}

#endif