#pragma once

#include <boost/spirit/include/qi.hpp>
#include "ast.h"

using namespace ast;

struct eval : boost::static_visitor<bool> {
    eval() {}

    bool operator()(const var& v) const;

    bool operator()(const binop<op_imp>& b) const;
    bool operator()(const binop<op_and>& b) const;
    bool operator()(const binop<op_or>& b) const;
    bool operator()(const unop<op_not>& u) const;

    private:
    template<typename T>
    bool recurse(T const& v) const;
};