#ifndef SQL_FORMATTER_H_
#define SQL_FORMATTER_H_

#include <string>
#include "absl/status/status.h"
absl::Status FormatSql(const std::string& sql, std::string* formatted_sql);
#endif