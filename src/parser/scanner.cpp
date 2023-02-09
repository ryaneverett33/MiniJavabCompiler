#include "scanner.h"
#include "parserdriver.h"
#include "parser.h"
#include <string>

namespace MiniJavab {
namespace Parser {

MiniJavab::AST::Node* ParseFileToAST(const std::string& f) {
    ParserDriver driver;
    driver.ScanFile(f);
    yy::parser parser(driver);
//#ifdef YYDEBUG
//    parser.set_debug_level(1);
//#endif
    int parseResult = parser.parse();
    driver.FinishScanning();
    if (parseResult == 0) {
        return driver.Result;
    }
    return nullptr;
}

}} // end namespace