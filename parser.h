#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include "ast.h"

using namespace ast;
namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

template <typename It, typename Skipper = qi::space_type>
struct parser : qi::grammar<It, expr(), Skipper> {
    parser() : parser::base_type(expr_) {};
    private:
    qi::rule<It, var() , Skipper> var_;
    qi::rule<It, expr(), Skipper> imp_, not_, and_, or_, simple, expr_; 
};