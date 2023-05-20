#pragma once

#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include "ast.h"

using namespace ast;

struct printer : boost::static_visitor<void> {
    printer(std::ostream& os);
    std::ostream& _os;

    void operator()(const var& v) const;

    void operator()(const binop<op_imp>& b) const;
    void operator()(const binop<op_and>& b) const;
    void operator()(const binop<op_or >& b) const;

    void print(const std::string& op, const expr& l, const expr& r) const;

    void operator()(const unop<op_not>& u) const;
};