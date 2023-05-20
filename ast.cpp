#include "ast.h"

template <typename t> 
ast::binop<t>::binop(const ast::expr& l, const ast::expr& r) : oper1(l), oper2(r) {}

template <typename t> 
ast::unop<t>::unop(const ast::expr& o) : oper1(o) {}
