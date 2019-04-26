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
  // don't skip the whitespace while reading
  std::cin >> std::noskipws;

  // use stream iterators to copy the stream to a string
  std::istream_iterator<char> it(std::cin);
  std::istream_iterator<char> end;
  std::string results(it, end);
  std::cout << formatSql(results);
}
