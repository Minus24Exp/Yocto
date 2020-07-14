#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include <vector>
#include <memory>

struct Node;

struct Stmt;
struct ExprStmt;
struct VarDecl;
struct Block;
struct FuncDecl;
struct ReturnStmt;
struct WhileStmt;
struct ClassDecl;

struct Expr;
struct Literal;
struct Identifier;
struct Infix;
struct Prefix;
struct Postfix;
struct Assign;
struct SetExpr;
struct GetExpr;
struct FuncCall;
struct IfExpr;
struct ArrayExpr;
struct GetItem;
struct SetItem;

class BaseVisitor {
public:
    BaseVisitor() {}
    virtual ~BaseVisitor() = default;
        
    // Statements //
    virtual void visit(ExprStmt * expr_stmt) = 0;
    virtual void visit(Block * block) = 0;
    virtual void visit(VarDecl * var_decl) = 0;
    virtual void visit(FuncDecl * func_decl) = 0;
    virtual void visit(ReturnStmt * return_stmt) = 0;
    virtual void visit(WhileStmt * w) = 0;
    virtual void visit(ClassDecl * class_decl) = 0;

    // Expressions //
    virtual void visit(Literal * literal) = 0;
    virtual void visit(Identifier * id) = 0;
    virtual void visit(Infix * infix) = 0;
    virtual void visit(Prefix * prefix) = 0;
    virtual void visit(Postfix * postfix) = 0;
    virtual void visit(Assign * assign) = 0;
    virtual void visit(SetExpr * set_expr) = 0;
    virtual void visit(GetExpr * get_expr) = 0;
    virtual void visit(FuncCall * func_call) = 0;
    virtual void visit(IfExpr * if_expr) = 0;
    virtual void visit(ArrayExpr * array) = 0;
    virtual void visit(GetItem * get_item) = 0;
    virtual void visit(SetItem * set_item) = 0;
    
};

#endif