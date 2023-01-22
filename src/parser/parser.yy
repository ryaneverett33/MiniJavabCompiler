%skeleton "lalr1.cc"
%require "3.4"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
#include <stdio.h>
#include "ast/ast.h"
using namespace MiniJavab::AST;
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
  INCREMENT "++"
  DECREMENT "--"
  BOOLAND "&&"
  BOOLOR "||"
  BOOLEQUAL "=="
  BOOLNOTEQUAL "!="
  LTEQUAL "<="
  GTEQUAL ">="
  LEFTSBRACE "{"
  RIGHTSBRACE "}"
  LEFTBRACE "["
  RIGHTBRACE "]"
  LEFTPAREN "("
  RIGHTPAREN ")"
  SEMICOLON ";"
  GT ">"
  LT "<"
  PLUS "+"
  MINUS "-"
  STAR "*"
  SLASH "/"
  EXCLAMATION "!"
  DOT "."
  COMMA ","
  EQUAL "="
;
%token <int> INTEGER_LITERAL
%token <std::string> ID "id"
%token <std::string> STRING_LITERAL
%type <ExpNode*> exp
%type <ExpNode*> program
%type <ExpNode*> mainclass
%type <ExpNode*> classdecllist
%type <ExpNode*> classdecl
%type <ExpNode*> methoddecllist
%type <ExpNode*> methoddecl
%type <ExpNode*> formallist
%type <ExpNode*> formalrestlist
%type <ExpNode*> formalrest
%type <TypeNode*> type
%type <TypeNode*> primetype
%type <TypeNode*> typeb
%type <TypeNode*> primetypeb
%type <ExpNode*> vardecllist
%type <ExpNode*> vardecl
%type <ExpNode*> object
%type <ExpNode*> objectb
%type <ExpNode*> statementlist
%type <ExpNode*> statement
%type <ExpNode*> index
%type <ExpNode*> explist
%type <ExpNode*> exprestlist
%type <ExpNode*> exprest

%printer { yyo << $$; } <*>

%%

%start unit;
unit: program { 
            drv.result = $1; 
}
  ;
%left "==" "!=";
%left "&&" "||";
%left "<=" ">=";
%left "<" ">";
%left "!";
%left "*" "/";
%left "+" "-";

program: mainclass classdecllist { $$ = new ExpNode({}); }

mainclass: CLASS ID "{" MAINCLASS "(" STRINGTY "[" "]" ID ")" "{" statement "}" "}" { $$ = new ExpNode({}); }
        ;

classdecllist: classdecllist classdecl { $$ = new ExpNode({}); }
            | { $$ = new ExpNode({}); }
            ;

classdecl: CLASS ID "{" vardecllist methoddecllist "}" { $$ = new ExpNode({}); }
        | CLASS ID EXTENDS ID "{" vardecllist methoddecllist "}" { $$ = new ExpNode({}); }
        ;

methoddecllist: methoddecllist methoddecl { $$ = new ExpNode({}); }
            | { $$ = new ExpNode({}); }
            ;

methoddecl: PUBLIC type ID "(" formallist ")" "{" vardecllist statementlist RETURN exp ";" "}" { $$ = new ExpNode({}); }
        | PUBLIC type ID "(" formallist ")" "{" vardecllist RETURN exp ";" "}" { $$ = new ExpNode({}); }
        ;

formallist: type ID formalrestlist { $$ = new ExpNode({}); }
        | { $$ = new ExpNode({}); }
        ;

formalrestlist: formalrestlist formalrest { $$ = new ExpNode({}); }
        | { $$ = new ExpNode({}); }
        ;

formalrest: "," type ID { $$ = new ExpNode({}); }
        ;

type: primetype { $$ = $1; }
    | type "[" "]" { 
      assert(dynamic_cast<ArrayTypeNode*>($1) == nullptr && "Didn't expect this to be an array already");
      $$ = new ArrayTypeNode($1); 
    }
    ;

primetype: INTTY { $$ = new IntegerTypeNode(); }
        | BOOLEANTY { $$ = new BooleanTypeNode(); }
        | ID { $$ = new ObjectTypeNode($1); }
        ;

typeb: primetypeb { $$ = $1; }
    | typeb "[" "]" { 
      if (ArrayTypeNode* arrayNode = dynamic_cast<ArrayTypeNode*>($1)) {
        arrayNode->Increase(); $$ = $1;
      }
      else {
        $$ = new ArrayTypeNode($1);
      }
    }
    | ID "[" "]" { $$ = new ArrayTypeNode(new ObjectTypeNode($1)); }
    ;

primetypeb: INTTY { $$ = new IntegerTypeNode(); }
        | BOOLEANTY { $$ = new BooleanTypeNode(); }
        ;

vardecllist: vardecllist vardecl { $$ = new ExpNode({}); }
        | { $$ = new ExpNode({}); }
        ;

vardecl: typeb ID ";" { $$ = new ExpNode({}); }
      | ID ID ";" { $$ = new ExpNode({}); }
      ;

object: ID { $$ = new ExpNode({}); }
    | THIS { $$ = new ExpNode({}); }
    | NEW ID "(" ")" { $$ = new ExpNode({}); }
    | NEW primetype index { $$ = new ExpNode({}); }
    ;

objectb: THIS { $$ = new ExpNode({}); }
    | NEW ID "(" ")" { $$ = new ExpNode({}); }
    | NEW primetype index { $$ = new ExpNode({}); }
    ;

statementlist: statementlist statement { $$ = new ExpNode({}); }
    | statement { $$ = new ExpNode({}); }
    ;

statement: "{" statementlist "}" { $$ = new ExpNode({}); }
      | "{" "}" { $$ = new ExpNode({}); }
      | IF "(" exp ")" statement ELSE statement { $$ = new ExpNode({}); }
      | WHILE "(" exp ")" statement { $$ = new ExpNode({}); }
      | PRINTLN "(" exp ")" ";" { $$ = new ExpNode({}); }
      | PRINTLN "(" STRING_LITERAL ")" ";" { $$ = new ExpNode({}); }
      | PRINT "(" exp ")" ";" { $$ = new ExpNode({}); }
      | PRINT "(" STRING_LITERAL ")" ";" { $$ = new ExpNode({}); }
      | ID "=" exp ";" { $$ = new ExpNode({}); }
      | ID index "=" exp ";" { $$ = new ExpNode({}); }
      | RETURN exp ";" { $$ = new ExpNode({}); }
      ;

index: "[" exp "]" { $$ = new ExpNode({}); }
    | index "[" exp "]" { $$ = new ExpNode({}); }
    ;


exp: exp "&&" exp { $$ = new BinaryExpNode(OperatorType::BooleanAnd, $1, $3);}
  | exp "||" exp { $$ = new BinaryExpNode(OperatorType::BooleanOr, $1, $3);}
  | exp "==" exp { $$ = new BinaryExpNode(OperatorType::EqualTo, $1, $3);}
  | exp "!=" exp { $$ = new BinaryExpNode(OperatorType::NotEqualTo, $1, $3);}
  | exp "<=" exp { $$ = new BinaryExpNode(OperatorType::LessThanEqualTo, $1, $3);}
  | exp ">=" exp { $$ = new BinaryExpNode(OperatorType::GreaterThanEqualTo, $1, $3);}
  | exp "<" exp { $$ = new BinaryExpNode(OperatorType::LessThan, $1, $3);}
  | exp ">" exp { $$ = new BinaryExpNode(OperatorType::GreaterThan, $1, $3);}
  | exp "+" exp { $$ = new BinaryExpNode(OperatorType::Add, $1, $3);}
  | exp "-" exp { $$ = new BinaryExpNode(OperatorType::Subtract, $1, $3);}
  | exp "*" exp { $$ = new BinaryExpNode(OperatorType::Multiple, $1, $3);}
  | exp "/" exp { $$ = new BinaryExpNode(OperatorType::Divide, $1, $3);}
  | "!" exp { $$ = new UnaryExpNode(OperatorType::Factorial, $2);}
  | "-" exp { $$ = new UnaryExpNode(OperatorType::Subtract, $2);}
  | "+" exp { $$ = new UnaryExpNode(OperatorType::Add, $2);}
  | INTEGER_LITERAL { $$ = new IntegerLiteralExpNode($1); }
  | STRING_LITERAL { $$ = new StringLiteralExpNode($1); }
  | TRUE { $$ = new BooleanLiteralExpNode(true); }
  | FALSE { $$ = new BooleanLiteralExpNode(false); }
  | object { $$ = new ExpNode({}); /*todo*/}
  | "(" exp ")" { $$ = new ExpNode({}); /*todo*/}
  | ID index { $$ = new ExpNode({}); }
  | ID "." LENGTH { $$ = new ExpNode({}); }
  | ID index "." LENGTH { $$ = new ExpNode({}); }
  | ID "." ID "(" explist ")" { $$ = new ExpNode({}); }
  | objectb "." ID "(" explist ")" { $$ = new ExpNode({}); }
  ;

explist: exp exprestlist { $$ = new ExpNode({}); }
    | { $$ = new ExpNode({}); }
    ;

exprestlist: exprestlist exprest { $$ = new ExpNode({}); }
        | { $$ = new ExpNode({}); }
        ;

exprest: "," exp { $$ = new ExpNode({}); }
      ;
  
%%

void yy::parser::error(const location_type& loc, const std::string& m) {
  std::cerr << loc << ": " << m << std::endl;
}
