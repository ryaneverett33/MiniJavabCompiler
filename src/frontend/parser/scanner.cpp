#include "scanner.h"
#include "parser.h"
#include "parserdriver.h"
#include <string>

namespace MiniJavab {
namespace Frontend {
namespace Parser {

ScanResult* ParseFileToAST(const std::string& f) {
    ParserDriver driver;
    driver.ScanFile(f);
    yy::parser parser(driver);
//#ifdef YYDEBUG
//    parser.set_debug_level(1);
//#endif
    int parseResult = parser.parse();
    driver.FinishScanning();
    return new ScanResult(driver.Result, nullptr);
}

}}} // end namespace