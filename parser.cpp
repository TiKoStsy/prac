#include "parser.h"
template <typename It, typename Skipper = qi::space_type>
parser<It, Skipper>::parser() : parser::base_type(expr_) {
    using namespace qi;

    expr_  = imp_.alias();

    imp_ = (or_ >> "->" >> imp_ ) [ _val = phx::construct<binop<op_imp> >(_1, _2) ] | or_    [ _val = _1 ];
    or_  = (and_ >> '|'  >> or_ ) [ _val = phx::construct<binop<op_or > >(_1, _2) ] | and_   [ _val = _1 ];
    and_ = (not_ >> '&' >> and_)  [ _val = phx::construct<binop<op_and> >(_1, _2) ] | not_   [ _val = _1 ];
    not_ = ('!' > simple       )  [ _val = phx::construct<unop <op_not> >(_1)     ] | simple [ _val = _1 ];

    simple = (('(' > expr_ > ')') | var_);
    var_ = qi::lexeme[ +(alpha|digit) ];

    BOOST_SPIRIT_DEBUG_NODE(expr_);
    BOOST_SPIRIT_DEBUG_NODE(imp_);
    BOOST_SPIRIT_DEBUG_NODE(or_);
    BOOST_SPIRIT_DEBUG_NODE(and_);
    BOOST_SPIRIT_DEBUG_NODE(not_);
    BOOST_SPIRIT_DEBUG_NODE(simple);
    BOOST_SPIRIT_DEBUG_NODE(var_);
}