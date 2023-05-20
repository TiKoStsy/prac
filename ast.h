#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <iomanip>

namespace ast {     
    struct op_imp {};
    struct op_or  {};
    struct op_and {};
    struct op_not {};

    typedef std::string var; 
    template <typename t> struct binop;
    template <typename t> struct unop;

    typedef boost::variant<var, 
            boost::recursive_wrapper<binop<op_imp>>,
            boost::recursive_wrapper<unop <op_not>>, 
            boost::recursive_wrapper<binop<op_and>>,
            boost::recursive_wrapper<binop<op_or>>
            > expr;

    template <typename t> struct binop {
        explicit binop(const expr& l, const expr& r);
        expr oper1, oper2;
    };

    template <typename t> struct unop {
        explicit unop(const expr& o);
        expr oper1;
    };
};