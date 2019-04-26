#include "zetasql/parser/unparser.h"

#include <memory>
#include <iostream>

#include "zetasql/parser/parser.h"
int main() {
  std::string query_string("SELECT\n"
                      "  *\n"
                      "FROM\n"
                      "  foo\n");
  std::unique_ptr<zetasql::ParserOutput> parser_output;
  std::string unparsed_string = zetasql::Unparse(parser_output->statement());
  std::cout << unparsed_string;
}
