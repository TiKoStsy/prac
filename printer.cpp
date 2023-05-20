#include "printer.h"

printer::printer(std::ostream& os) : _os(os) {}

void printer::operator()(const var& v) const { _os << v; }
void printer::operator()(const binop<op_imp>& b) const { print("->", b.oper1, b.oper2); }
void printer::operator()(const binop<op_and>& b) const { print("&", b.oper1, b.oper2); }
void printer::operator()(const binop<op_or >& b) const { print("|", b.oper1, b.oper2); }

void printer::print(const std::string& op, const expr& l, const expr& r) const {
    _os << "op:" << op;
    _os << "(";
    boost::apply_visitor(*this, l);
    _os << ",";
    boost::apply_visitor(*this, r);
    _os << ")";
}

void printer::operator()(const unop<op_not>& u) const {
    _os << "op:!";
    _os << "(";
    boost::apply_visitor(*this, u.oper1);
    _os << ")";
} 