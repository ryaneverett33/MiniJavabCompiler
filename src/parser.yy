%skeleton "lalr1.cc"
%require "3.4"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
#include <stdio.h>
class Driver;
}

%param { Driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
#include "driver.h"
#include <iostream>
#include <string>
}

%define api.token.prefix {TOK_}
%token
  END 0 "end of file"
  PRINTLN "System.out.println"
  PRINT "System.out.print"
  INTTY "int"
  VOIDTY "void"
  IF "if"
  ELSE "else"
  WHILE "while"
  TRUE "true"
  FALSE "false"
  OBJECTTY "Object"
  THIS "this"
  NEW "new"
  MAINCLASS "public static void main"
  CLASS "class"
  PUBLIC "public"
  STRINGTY "String"
  RETURN "return"
  LENGTH "length"
  BOOLEANTY "boolean"
  EXTENDS "extends"
  PLUS "+"
  MINUS "-"
  MULTIPLY "*"
  DIVIDE "/"
  FACTORIAL "!"
  INCREMENT "++"
  DECREMENT "--"
  BOOLAND "&&"
  BOOLOR "||"
  BOOLEQUAL "=="
  BOOLNOTEQUAL "!="
  GT ">"
  LT "<"
  LTEQUAL "<="
  GTEQUAL ">="
;
%token <int> INTEGER_LITERAL
%token <std::string> ID "id"
%token <std::string> STRING_LITERAL
%type <int> exp

%printer { yyo << $$; } <*>

%%

%start unit;
unit: exp { 
            drv.result = $1; 
}
  ;

%left "+" "-";
%left "*" "/";

exp: INTEGER_LITERAL { $$ = $1; }
  | exp "+" exp { $$ = $1 + $3; }
  | exp "-" exp { $$ = $1 - $3; }
  | exp "/" exp { $$ = $1 / $3; }
  | STRING_LITERAL { printf($1.c_str()); $$ = 1;}
  ;

%%

void yy::parser::error(const location_type& loc, const std::string& m) {
  std::cerr << loc << ": " << m << std::endl;
}
