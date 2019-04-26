#include "zetasql/parser/unparser.h"

#include <memory>
#include <iostream>

#include "zetasql/parser/parser.h"

std::string formatSql(std::string sql) {
  std::unique_ptr<zetasql::ParserOutput> parser_output;
  zetasql::ParseStatement(sql, zetasql::ParserOptions(), &parser_output);
  return zetasql::Unparse(parser_output->statement());
}

int main(int argc, char *argv[]) {
  std::string query_string(argv[1]);
  std::cout << formatSql(query_string);
}

