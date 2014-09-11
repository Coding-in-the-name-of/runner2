#ifndef LANG_GRAMMAR_HPP
#define LANG_GRAMMAR_HPP



#include "elements.hpp"

#include <string>



namespace Lang
{



bool Parse(const std::string& code, Unit& unit);



}



#endif // LANG_GRAMMAR_HPP
