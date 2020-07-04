#include <memory>
#include <iostream>
#include <string.h>

#include "sql_formatter.h"
#include "zetasql/public/sql_formatter.h"

#include "formatsql.h"

char *formatSqlC(char* sql) {
  std::string formatted_sql;
  const auto result = FormatSql(std::string(sql), &formatted_sql);
  return strdup(formatted_sql.c_str());
}
