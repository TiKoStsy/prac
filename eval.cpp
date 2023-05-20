#include "eval.h"

bool eval::operator()(const var& v) const {
    if (v=="T" || v=="t" || v=="true" || v=="True")
        return true;
    else if (v=="F" || v=="f" || v=="false" || v=="False")
        return false;
    std::cout << "Value of " << v << ": ";
    bool val;
    std::cin >> val;
    return val;
}

bool eval::operator()(const binop<op_imp>& b) const {
        return !recurse(b.oper1) || recurse(b.oper2);
}

bool eval::operator()(const binop<op_and>& b) const {
    return recurse(b.oper1) && recurse(b.oper2);
}
bool eval::operator()(const binop<op_or>& b) const {
    return recurse(b.oper1) || recurse(b.oper2);
}
bool eval::operator()(const unop<op_not>& u) const {
    return !recurse(u.oper1);
} 

template<typename T>
bool eval::recurse(T const& v) const{ 
    return boost::apply_visitor(*this, v); 
}