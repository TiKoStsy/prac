#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include "ast.h"
#include "eval.h"
#include "printer.h"
#include "parser.h"

using namespace ast;

bool evaluate(const expr& e) { return boost::apply_visitor(eval(), e); }

std::ostream& operator<<(std::ostream& os, const expr& e) { boost::apply_visitor(printer(os), e); return os; }

int main() {
    const std::string inputs[] = { 
        std::string("x & y;"),
        std::string("ttt | x & y;"),
        std::string("x;"),
        std::string("t;"),
        std::string("t & !f -> (t | t);"),

        std::string("T&F;"),
        std::string("T&!F;"),
        std::string("!T&F;"),
        std::string("T|F;"),
        std::string("T->!F;"),
        std::string("")
    };

    for (const std::string *i = inputs; !i->empty(); ++i) {
        typedef std::string::const_iterator It;
        It f(i->begin()), l(i->end());
        parser<It> p;

        try {
            expr result;
            bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

            if (!ok)
                std::cerr << "invalid input\n";
            else {
                std::cout << "expression:\t" << *i << "\n";
                std::cout << "result:\t" << result << "\n";
                std::cout << "evaluated:\n" << evaluate(result) << "\n\n";
            }

        } catch (const qi::expectation_failure<It>& e) {
            std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'\n";
        }

        if (f!=l) std::cerr << "unparsed: '" << std::string(f,l) << "'\n";
    }

    return 0; 
}