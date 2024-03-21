%skeleton "lalr1.cc"
%require "3.4"
%defines

%define api.token.constructor
%verbose
%define api.value.type variant
%define parse.trace

%code requires {
#include <string>
#include <vector>
#include <cassert>
#include <stdio.h>
#include "minijavab/frontend/ast/ast.h"
using namespace MiniJavab::Frontend::AST;
class ParserDriver;
class Error;
}

%param { ParserDriver& driver }

%locations

%define parse.error verbose
%verbose

%code {
#include "minijavab/frontend/parser/parserdriver.h"
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
%type <ProgramNode*> program
%type <ClassDeclNode*> mainclass
%type <std::vector<ClassDeclNode*>> classdecllist
%type <ClassDeclNode*> classdecl
%type <std::vector<MethodDeclNode*>> methoddecllist
%type <MethodDeclNode*> methoddecl
%type <std::vector<VarDeclNode*>> formallist
%type <std::vector<VarDeclNode*>> formalrestlist
%type <VarDeclNode*> formalrest
%type <TypeNode*> type
%type <TypeNode*> primetype
%type <TypeNode*> typeb
%type <TypeNode*> primetypeb
%type <std::vector<VarDeclNode*>> vardecllist
%type <VarDeclNode*> vardecl
%type <ObjectNode*> object
%type <ObjectNode*> objectb
%type <std::vector<StatementNode*>> statementlist
%type <StatementNode*> statement
%type <IndexNode*> index
%type <std::vector<ExpNode*>> explist
%type <std::vector<ExpNode*>> exprestlist
%type <ExpNode*> exprest

%printer {
  yyo << "shit's a vector" << std::endl;
} classdecllist methoddecllist formallist formalrestlist vardecllist statementlist explist exprestlist
%printer {
  yyo << $$;
} <*>

%%

%start unit;
unit: program { 
            driver.Result = $1; 
}
  ;
%left "==" "!=";
%left "&&" "||";
%left "<=" ">=";
%left "<" ">";
%left "!";
%left "*" "/";
%left "+" "-";

program: mainclass[main] classdecllist[list] { $$ = new ProgramNode($main, $list); }

mainclass: CLASS ID[name] "{" MAINCLASS "(" STRINGTY "[" "]" ID[args] ")" "{" statement "}" "}" 
        { 
          MainMethodDeclNode* mainMethod = new MainMethodDeclNode($args, $statement);
          $$ = new ClassDeclNode($name, {}, {mainMethod});
        }
        ;

classdecllist: classdecllist[list] classdecl[decl] { $list.push_back($decl); $$ = $list; }
            | { $$ = std::vector<ClassDeclNode*>(); }
            ;

classdecl: CLASS ID[name] "{" vardecllist[variables] methoddecllist[methods] "}" { $$ = new ClassDeclNode($name, $variables, $methods); }
        | CLASS ID[name] EXTENDS ID[baseClass] "{" vardecllist[variables] methoddecllist[methods] "}" { $$ = new ClassDeclNode($name, $baseClass, $variables, $methods); }
        ;

methoddecllist: methoddecllist[list] methoddecl[method] { $list.push_back($method); $$ = $list; }
            | { $$ = std::vector<MethodDeclNode*>(); }
            ;

methoddecl: PUBLIC type ID[name] "(" formallist[parameters] ")" "{" vardecllist[variables] statementlist[statements] RETURN exp ";" "}" 
          { $$ = new MethodDeclNode($type, $name, $parameters, $variables, $statements, $exp); }
        | PUBLIC type ID[name] "(" formallist[parameters] ")" "{" vardecllist[variables] RETURN exp ";" "}" 
          { $$ = new MethodDeclNode($type, $name, $parameters, $variables, {}, $exp); }
        ;

formallist: type ID formalrestlist[list] { $list.push_back(new VarDeclNode($type, $ID)); $$ = $list; }
        | { $$ = std::vector<VarDeclNode*>(); }
        ;

formalrestlist: formalrestlist[list] formalrest[param] { $list.push_back($param); $$ = $list; }
        | { $$ = std::vector<VarDeclNode*>(); }
        ;

formalrest: "," type ID { $$ = new VarDeclNode($type, $ID); }
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

vardecllist: vardecllist[list] vardecl[decl] { $list.push_back($decl); $$ = $list; }
        | { $$ = std::vector<VarDeclNode*>(); }
        ;

vardecl: typeb[type] ID[name] ";" { $$ = new VarDeclNode($type, $name); }
      | ID[type] ID[name] ";" { $$ = new VarDeclNode($type, $name); }
      ;

object: ID { $$ = new NamedObjectNode($ID); }
    | THIS { $$ = new ThisObjectNode(); }
    | NEW ID "(" ")" { $$ = new NewObjectNode($ID); }
    | NEW primetype[type] index { $$ = new NewArrayObjectNode($type, $index); }
    ;

objectb: THIS { $$ = new ThisObjectNode(); }
    | NEW ID "(" ")" { $$ = new NewObjectNode($ID); }
    | NEW primetype[type] index { $$ = new NewArrayObjectNode($type, $index); }
    ;

statementlist: statementlist[list] statement 
          { $list.push_back($statement); $$ = $list; }
    | statement { $$ = {$statement}; }
    ;

statement: "{" statementlist[list] "}" { $$ = new NestedStatementsNode($list); }
      | "{" "}" { $$ = new NestedStatementsNode({});}
      | IF "(" exp ")" statement[ifState] ELSE statement[elseState] { $$ = new IfStatementNode($exp, $ifState, $elseState); }
      | WHILE "(" exp ")" statement[state] { $$ = new WhileStatementNode($exp, $state); }
      | PRINTLN "(" exp ")" ";" { $$ = new PrintExpStatementNode($exp, true); }
      | PRINTLN "(" STRING_LITERAL[string] ")" ";" { $$ = new PrintStringStatementNode($string, true); }
      | PRINT "(" exp ")" ";" { $$ = new PrintExpStatementNode($exp); }
      | PRINT "(" STRING_LITERAL[string] ")" ";" { $$ = new PrintStringStatementNode($string); }
      | ID "=" exp ";" { $$ = new AssignmentStatementNode($ID, $exp); }
      | ID index "=" exp ";" { $$ = new AssignmentIndexStatementNode($ID, $index, $exp); }
      | RETURN exp ";" { $$ = new ReturnStatementNode($exp);}
      ;

index: "[" exp "]" { $$ = new IndexNode($exp); }
    | index[in] "[" exp "]" { $in->Expressions.push_back($exp); $$ = $in; }
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
  | exp "*" exp { $$ = new BinaryExpNode(OperatorType::Multiply, $1, $3);}
  | exp "/" exp { $$ = new BinaryExpNode(OperatorType::Divide, $1, $3);}
  | "!" exp { $$ = new UnaryExpNode(OperatorType::Factorial, $2);}
  | "-" exp { $$ = new UnaryExpNode(OperatorType::Subtract, $2);}
  | "+" exp { $$ = new UnaryExpNode(OperatorType::Add, $2);}
  | INTEGER_LITERAL { $$ = new IntegerLiteralExpNode($1); }
  | STRING_LITERAL { $$ = new StringLiteralExpNode($1); }
  | TRUE { $$ = new BooleanLiteralExpNode(true); }
  | FALSE { $$ = new BooleanLiteralExpNode(false); }
  | object { $$ = new ObjectExpNode($object);}
  | "(" exp[e] ")" { $$ = new NestedExpNode($e);}
  | ID index { $$ = new IndexExpNode($ID, $index);}
  | ID "." LENGTH { $$ = new LengthExpNode($ID);}
  | ID index "." LENGTH { $$ = new LengthExpNode($ID, $index);}
  | ID[object] "." ID[method] "(" explist ")" { $$ = new MethodCallExpNode($object, $method, $explist);}
  | objectb[object] "." ID[method] "(" explist ")" { $$ = new MethodCallExpNode($object, $method, $explist);}
  ;

explist: exp exprestlist[list] { $list.push_back($exp); $$ = $list; }
    | { $$ = std::vector<ExpNode*>(); }
    ;

exprestlist: exprestlist[list] exprest[exp] { $list.push_back($exp); $$ = $list; }
        | { $$ = std::vector<ExpNode*>(); }
        ;

exprest: "," exp { $$ = $exp; }
      ;
  
%%

void yy::parser::error(const location_type& loc, const std::string& m) {
  driver.LastError = new Error(m, loc);
}
