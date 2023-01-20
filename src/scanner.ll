%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include "driver.h"
#include "parser.h"
%}

%option noyywrap
%option nounput noinput
%option batch
/*%option debug*/

%{
yy::parser::symbol_type make_INTEGER_LITERAL(
    const std::string &s, const yy::parser::location_type& loc);
yy::parser::symbol_type make_STRING_LITERAL(
    const std::string &s, const yy::parser::location_type& loc);
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]

%{
#define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
yy::location& loc = drv.location;
loc.step();
%}

[ \t\r] loc.step();
\n+ loc.lines(yyleng); loc.step();

[ \n]|(\r\n)               {yylineno++;}

"System.out.println"        return yy::parser::make_PRINTLN(loc);
"System.out.print"          return yy::parser::make_PRINT(loc);
"length"                    return yy::parser::make_LENGTH(loc);
"new"                       return yy::parser::make_NEW(loc);

"int"                       return yy::parser::make_INTTY(loc);
"void"                      return yy::parser::make_VOIDTY(loc);
"String"                    return yy::parser::make_STRINGTY(loc);
"Object"                    return yy::parser::make_OBJECTTY(loc);
"boolean"                   return yy::parser::make_BOOLEANTY(loc);

"true"                      return yy::parser::make_TRUE(loc);
"false"                     return yy::parser::make_FALSE(loc);
"this"                      return yy::parser::make_THIS(loc);

"if"                        return yy::parser::make_IF(loc);
"else"                      return yy::parser::make_ELSE(loc);
"while"                     return yy::parser::make_WHILE(loc);
"return"                    return yy::parser::make_RETURN(loc);

"public static void main"   return yy::parser::make_MAINCLASS(loc);
"class"                     return yy::parser::make_CLASS(loc);
"public"                    return yy::parser::make_PUBLIC(loc);

"extends"                   return yy::parser::make_EXTENDS(loc);

"++"                        return yy::parser::make_INCREMENT(loc);
"--"                        return yy::parser::make_DECREMENT(loc);
"&&"                        return yy::parser::make_BOOLAND(loc);
"||"                        return yy::parser::make_BOOLOR(loc);
"=="                        return yy::parser::make_BOOLEQUAL(loc);
"!="                        return yy::parser::make_BOOLNOTEQUAL(loc);
">"                         return yy::parser::make_GT(loc);
"<"                         return yy::parser::make_LT(loc);
"<="                        return yy::parser::make_LTEQUAL(loc);
">="                        return yy::parser::make_GTEQUAL(loc);
"+"                         return yy::parser::make_PLUS(loc);
"-"                         return yy::parser::make_MINUS(loc);
"*"                         return yy::parser::make_MULTIPLY(loc);
"/"                         return yy::parser::make_DIVIDE(loc);
"!"                         return yy::parser::make_FACTORIAL(loc);

{DIGIT}+                        return make_INTEGER_LITERAL(yytext, loc);
{LETTER}+({LETTER}|{DIGIT}|_)*  return yy::parser::make_ID(yytext, loc);
\".*\"                          return make_STRING_LITERAL(yytext, loc);

. {
  throw yy::parser::syntax_error(
    loc, "invalid character: " + std::string(yytext));
}
<<EOF>> return yy::parser::make_END(loc);

%%

yy::parser::symbol_type make_INTEGER_LITERAL(
    const std::string& s, const yy::parser::location_type& loc) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_INTEGER_LITERAL((int)n, loc);
}

yy::parser::symbol_type make_STRING_LITERAL(
  const std::string& s, const yy::parser::location_type& loc) {
    errno = 0;
    return yy::parser::make_STRING_LITERAL(s.substr(1, s.length() - 2), loc);
}

void Driver::scan_begin() {
  if (file.empty() || file == "-") {
    yyin = stdin;
  } else if (!(yyin = fopen(file.c_str(), "r"))) {
    std::cerr << "cannot open " << file << ": " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Driver::scan_end() {
  fclose(yyin);
}
