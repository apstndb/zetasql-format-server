#include <memory>
#include <iostream>
#include <string.h>

#include "zetasql/parser/unparser.h"
#include "zetasql/parser/parser.h"
#include "formatsql.h"

std::string formatSql(const std::string& sql) {
  std::unique_ptr<zetasql::ParserOutput> parser_output;
  zetasql::ParseStatement(sql, zetasql::ParserOptions(), &parser_output);
  return zetasql::Unparse(parser_output->statement());
}

char *formatSqlC(char* sql) {
  const auto result = formatSql(std::string(sql));
  return strdup(result.c_str());
}
