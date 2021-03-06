//
// Copyright 2019 ZetaSQL Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "absl/strings/str_join.h"
#include "zetasql/base/ret_check.h"
#include "zetasql/parser/parser.h"
#include "zetasql/public/parse_resume_location.h"
#include "zetasql/public/parse_tokens.h"

#include "sql_formatter.h"
#include "unparser.h"

absl::Status FormatSql(const std::string &sql, std::string *formatted_sql)
{
  ZETASQL_RET_CHECK_NE(formatted_sql, nullptr);
  formatted_sql->clear();

  *formatted_sql = sql;

  std::vector<std::string> formatted_statement;

  zetasql::ParseResumeLocation location = zetasql::ParseResumeLocation::FromStringView(sql);
  bool at_end_of_input = false;
  absl::Status return_status = absl::OkStatus();

  zetasql::ParseResumeLocation pre_location = location;
  zetasql::ParseTokenOptions options;
  options.stop_at_end_of_statement = true;
  options.include_comments = true;

  bool last_token_is_comment = false;

  while (!at_end_of_input)
  {
    last_token_is_comment = false;

    std::unique_ptr<zetasql::ParserOutput> parser_output;

    const absl::Status status = ParseNextStatement(
        &location, zetasql::ParserOptions(), &parser_output, &at_end_of_input);

    if (status.ok())
    {
      std::string formatted;

      // Fetch comments in the last location range.
      std::vector<zetasql::ParseToken> parse_tokens;

      const absl::Status token_status =
          GetParseTokens(options, &pre_location, &parse_tokens);
      if (token_status.ok())
      {
        std::deque<std::pair<std::string, zetasql::ParseLocationPoint>> comments;
        for (const auto &parse_token : parse_tokens)
        {
          if (parse_token.IsEndOfInput())
            break;
          last_token_is_comment = false;
          if (parse_token.IsComment())
          {
            last_token_is_comment = true;
            comments.push_back(std::make_pair(parse_token.GetSQL(), parse_token.GetLocationRange().start()));
          }
        }
        formatted = UnparseWithComments(parser_output->statement(), comments);
      }
      else
      {
        // If GetParseTokens fails, just ignores comments.
        formatted = Unparse(parser_output->statement());
      }
      formatted_statement.push_back(formatted);
    }
    else
    {
      const absl::Status out_status = zetasql::MaybeUpdateErrorFromPayload(
          zetasql::ErrorMessageMode::ERROR_MESSAGE_MULTI_LINE_WITH_CARET, sql, status);
      if (return_status.ok())
      {
        return_status = out_status;
      }
      else
      {
        return_status = ::zetasql_base::StatusBuilder(return_status).SetAppend()
                        << "\n"
                        << zetasql::FormatError(out_status);
      }

      // When statement is not parseable, we proceed to the next semicolon and
      // just emit the original string in between.
      std::vector<zetasql::ParseToken> parse_tokens;
      zetasql::ParseTokenOptions options;
      options.stop_at_end_of_statement = true;

      const int statement_start = location.byte_position();
      const absl::Status token_status =
          GetParseTokens(options, &location, &parse_tokens);
      // If GetParseTokens fails, just returns the original sql since there's no
      // way to proceed forward.
      if (!token_status.ok())
      {
        return zetasql::MaybeUpdateErrorFromPayload(
            zetasql::ErrorMessageMode::ERROR_MESSAGE_MULTI_LINE_WITH_CARET, sql,
            token_status);
      }
      // GetParseTokens() reads until either a semicolon or end of input.
      if (parse_tokens.back().IsEndOfInput())
      {
        // When there's trailing whitespace or comment after the last
        // semicolon, parse_tokens will be one END_OF_INPUT token.
        // It should not be treated as a statement. If there's more than one
        // token, then we treat the remainder of the input as a statement.
        if (parse_tokens.size() != 1)
        {
          formatted_statement.push_back(sql.substr(statement_start));
        }
        at_end_of_input = true;
      }
      else
      {
        // The last token parsed must be a semicolon. Do not include it, because
        // we will add one later.
        ZETASQL_RET_CHECK_EQ(parse_tokens.back().GetKeyword(), ";");
        const int statement_length =
            parse_tokens.back().GetLocationRange().start().GetByteOffset() -
            statement_start;
        formatted_statement.push_back(
            sql.substr(statement_start, statement_length));
      }
    }
  }

  // The result from Unparse always ends with '\n'. Strips whitespaces so ';'
  // can follow the statement immediately rather than starting a new line.
  for (auto &e : formatted_statement)
  {
    absl::StripAsciiWhitespace(&e);
  }

  std::string suffix;
  if (last_token_is_comment)
  {
    suffix = "\n";
  }
  else
  {
    suffix = ";\n";
  }
  *formatted_sql = absl::StrCat(absl::StrJoin(formatted_statement, ";\n"), suffix);
  // Append comments finally because parser ignores comments and ; is not suitable
  // fot comments.
  std::vector<zetasql::ParseToken> parse_tokens;
  const absl::Status token_status = GetParseTokens(options, &pre_location, &parse_tokens);
  if (token_status.ok())
  {
    for (const auto &parse_token : parse_tokens)
    {
      if (parse_token.IsComment())
      {
        *formatted_sql = absl::StrCat(*formatted_sql, parse_token.GetSQL());
      }
    }
  }
  return return_status;
}