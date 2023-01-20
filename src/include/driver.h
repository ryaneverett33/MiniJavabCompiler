#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <map>
#include "parser.h"

#define YY_DECL \
  yy::parser::symbol_type yylex (Driver& drv)
YY_DECL;

class Driver {
 public:
  Driver() {}
  int result;
  int parse(const std::string& f);
  std::string file;
  void scan_begin();
  void scan_end();
  yy::location location;
};

#endif // DRIVER_H_
