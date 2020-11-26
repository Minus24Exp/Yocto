#ifndef SETITEM_H
#define SETITEM_H

#include "tree/Expr/Expr.h"

namespace jc::tree {
    struct SetItem : Expr {
        expr_ptr left;
        expr_ptr index;
        expr_ptr value;

        SetItem(expr_ptr left,
                expr_ptr index,
                expr_ptr value)
                : Expr(left->pos, ExprType::SetItem), left(left), index(index), value(value) {}

        void accept(BaseVisitor & visitor) override {
            visitor.visit(this);
        }
    };
}

#endif