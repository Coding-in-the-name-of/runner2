#include "grammar.hpp"
#include "elements.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_real.hpp>



namespace Lang
{



namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;



template <typename Iterator>
class Grammar : public qi::grammar<Iterator, Unit(), ascii::space_type>
{
public:
    Grammar()
      : Grammar::base_type(unit)
    {
        unit %=
            *statement
            >> qi::eps
        ;

        statement %=
            null_statement
        |   expression_statement
        ;

        expression_statement %=
            expression
            > ';'
        ;

        null_statement %=
            qi::char_(';')
        ;

        expression %=
            unary_expression
        ;

        unary_expression %=
           -(
                qi::char_('-')
            |   qi::char_('!')
            )
            > factor
        ;

        factor %=
            literal
        |   identifier
        |   ( '(' > expression > ')' )
        ;

        identifier %=
            qi::lexeme
            [
                (qi::alpha | qi::char_('_'))
                > *(qi::alnum | qi::char_('_'))
            ]
        ;

        literal %=
            real_literal
        |   string_literal
        ;

        real_literal %=
            qi::real_parser<Real, qi::ureal_policies<Real> >()
        ;

        string_literal %=
            qi::lexeme
            [
                '"'
                > *(qi::char_ - '"')
                > '"'
            ]
        ;

        unit.name("unit");
        statement.name("statement");
        expression_statement.name("expression statement");
        null_statement.name("null statement");
        expression.name("expression");
        unary_expression.name("unary expression");
        factor.name("factor");
        identifier.name("identifier");
        literal.name("literal");
        real_literal.name("real literal");
        string_literal.name("string literal");
    }

private:
    qi::rule<Iterator, Unit(), ascii::space_type> unit;
    qi::rule<Iterator, Statement(), ascii::space_type> statement;
    qi::rule<Iterator, ExpressionStatement(), ascii::space_type> expression_statement;
    qi::rule<Iterator, NullStatement(), ascii::space_type> null_statement;
    qi::rule<Iterator, Expression(), ascii::space_type> expression;
    qi::rule<Iterator, UnaryExpression(), ascii::space_type> unary_expression;
    qi::rule<Iterator, Factor(), ascii::space_type> factor;
    qi::rule<Iterator, Identifier(), ascii::space_type> identifier;
    qi::rule<Iterator, Var(), ascii::space_type> literal;
    qi::rule<Iterator, Real(), ascii::space_type> real_literal;
    qi::rule<Iterator, String(), ascii::space_type> string_literal;
};



bool Parse(const std::string& code, Unit& unit)
{
    static Grammar<std::string::const_iterator> grammar;

    std::string::const_iterator iter = code.begin();
    std::string::const_iterator end = code.end();

    bool r = qi::phrase_parse(iter, end, grammar, ascii::space, unit);

    return r && iter == end;
}



}
