#include "zetasql/parser/unparser.h"

#include <memory>
#include <iostream>

#include "zetasql/parser/parser.h"
#include "formatsql.h"

std::string formatSql(std::string sql) {
  std::unique_ptr<zetasql::ParserOutput> parser_output;
  zetasql::ParseStatement(sql, zetasql::ParserOptions(), &parser_output);
  return zetasql::Unparse(parser_output->statement());
}

char *formatSqlC(char* sql) {
  const auto result = formatSql(std::string(sql));
  char *c = (char *)malloc(result.length());
  strcpy(c, result.c_str());
  return c;
}
