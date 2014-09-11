#include "lang/grammar.hpp"

#include <iostream>
#include <iomanip>
#include <boost/spirit/include/qi_expect.hpp>



int main()
{
    std::string code = ";";
    Lang::Unit unit;

    try
    {
        std::cout << std::boolalpha << Lang::Parse(code, unit) << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& e)
    {
        std::cout << "Expectation failure\n" << std::string(e.first, e.last) << std::endl << e.what_ << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
    }

    return 0;
}
