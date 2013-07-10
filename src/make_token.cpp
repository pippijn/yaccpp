#include "node.h"
#include "ylcode.h"

namespace tokens
{

template<>
token *
make_token<DIR_TOKEN> (std::string const &string)
{
  return new token (DIR_TOKEN, string);
}

template<>token *
make_token<DIR_INCLUDE_ENUM> (std::string const &string)
{
  return new token (DIR_INCLUDE_ENUM, string);
}

template<>token *
make_token<DIR_EXPECT> (std::string const &string)
{
  return new token (DIR_EXPECT, string);
}

template<>token *
make_token<DIR_EXPECT_RR> (std::string const &string)
{
  return new token (DIR_EXPECT_RR, string);
}

template<>token *
make_token<DIR_DEFAULT_RULE_TYPE> (std::string const &string)
{
  return new token (DIR_DEFAULT_RULE_TYPE, string);
}

template<>token *
make_token<DIR_DEFAULT_TOKEN_TYPE> (std::string const &string)
{
  return new token (DIR_DEFAULT_TOKEN_TYPE, string);
}

template<>token *
make_token<DIR_TYPE> (std::string const &string)
{
  return new token (DIR_TYPE, string);
}

template<>token *
make_token<TK_CDECL> (std::string const &string)
{
  return new token (TK_CDECL, string);
}

template<>token *
make_token<TK_SEPARATOR> (std::string const &string)
{
  return new token (TK_SEPARATOR, string);
}

template<>token *
make_token<TK_ELLIPSIS> (std::string const &string)
{
  return new token (TK_ELLIPSIS, string);
}

template<>token *
make_token<TK_YACCVAR> (std::string const &string)
{
  return new yaccvar (string);
}

template<>token *
make_token<TK_DIRECTIVE> (std::string const &string)
{
  return new token (TK_DIRECTIVE, string);
}

template<>token *
make_token<TK_TYPE> (std::string const &string)
{
  return new token (TK_TYPE, string);
}

template<>token *
make_token<TK_IDENTIFIER> (std::string const &string)
{
  return new identifier (string);
}

template<>token *
make_token<TK_INTEGER> (std::string const &string)
{
  return new token (TK_INTEGER, string);
}

template<>token *
make_token<TK_KEYWORD> (std::string const &string)
{
  return new token (TK_KEYWORD, string);
}

template<>token *
make_token<TK_STRING> (std::string const &string)
{
  return new token (TK_STRING, string);
}

template<>token *
make_token<TK_CHARACTER> (std::string const &string)
{
  return new token (TK_CHARACTER, string);
}

}
