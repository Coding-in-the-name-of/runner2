#ifndef LANG_ELEMENTS_HPP
#define LANG_ELEMENTS_HPP



#include <vector>
#include <string>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>



namespace Lang
{



typedef double Real;
typedef std::string String;
typedef boost::variant<Real, String> Var;

typedef char NullStatement;

struct Unit;
struct Statement;
struct ExpressionStatement;
struct Expression;
struct UnaryExpression;
struct Factor;
struct Identifier;



struct Identifier
{
    typedef String Type0;

    Type0 name;

    Identifier() : name() {}
    Identifier(const Type0& n) : name(n) {}
};

struct Factor
{
    typedef boost::variant< Var,
                            Identifier,
                            boost::recursive_wrapper<Expression>
                        > Type0;

    Type0 factor;

    Factor() : factor() {}
    Factor(const Type0& f) : factor(f) {}
};

struct UnaryExpression
{
    typedef boost::optional<char> Type0;
    typedef Factor Type1;

    Type0 op;
    Type1 expression;
};

struct Expression
{
    typedef UnaryExpression Type0;

    Type0 expression;

    Expression() : expression() {}
    Expression(const Type0& e) : expression(e) {}
};

struct ExpressionStatement
{
    typedef Expression Type0;

    Type0 expression;

    ExpressionStatement() : expression() {}
    ExpressionStatement(const Type0& e) : expression(e) {}
};

struct Statement
{
    typedef boost::variant< NullStatement,
                            ExpressionStatement
                        > Type0;

    Type0 statement;

    Statement() : statement() {}
    Statement(const Type0& s) : statement(s) {}
};

struct Unit
{
    typedef std::vector<Statement> Type0;

    Type0 statements;

    Unit() : statements() {}
    Unit(const Type0& s) : statements(s) {}
};



}



BOOST_FUSION_ADAPT_STRUCT
(
    Lang::Unit,
    (Lang::Unit::Type0, statements)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::Statement,
    (Lang::Statement::Type0, statement)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::ExpressionStatement,
    (Lang::ExpressionStatement::Type0, expression)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::Expression,
    (Lang::Expression::Type0, expression)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::UnaryExpression,
    (Lang::UnaryExpression::Type0, op)
    (Lang::UnaryExpression::Type1, expression)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::Factor,
    (Lang::Factor::Type0, factor)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Lang::Identifier,
    (Lang::Identifier::Type0, name)
)



#endif // LANG_ELEMENTS_HPP
