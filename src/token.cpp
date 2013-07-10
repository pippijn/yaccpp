#include "node.h"
#include "ylcode.h"

using namespace tokens;

identifier::identifier (std::string const &string)
  : token (TK_IDENTIFIER, string)
{
}

yaccvar::yaccvar (std::string const &string)
  : token (TK_YACCVAR, string)
{
}
