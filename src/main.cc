#include "config.h"

#include "lexer.h"
#include "parser.h"
#include "phases.h"
#include "sighandler.h"

#include <algorithm>
#include <clocale>
#include <cstdlib>
#include <stdexcept>

int
main (int argc, char *argv[])
try
{
  if (argc < 2)
    return EXIT_FAILURE;

  if (!strcmp (argv[1], "--version"))
    {
      puts (PACKAGE_NAME " v" PACKAGE_VERSION);
      return EXIT_SUCCESS;
    }

  if (!strcmp (argv[1], "--help"))
    {
      puts ("usage: yaccpp <file> [file]...");
      return EXIT_SUCCESS;
    }

  std::vector<std::string> files (argv + 1, argv + argc);;

#if 0
  std::copy (files.begin (), files.end (), std::ostream_iterator<std::string> (std::cout, "\n"));
#endif

  lexer lex (files);
  parser parse (lex);

  if (node_ptr doc = parse ())
    {
      phases::run ("nop", doc);
      phases::run ("anon_rules", doc);
      phases::run ("cardinality", doc);
      phases::run ("insert_syms", doc);
      phases::run ("scobind", doc);
      phases::run ("resolve_refs", doc);
      phases::run ("print", doc);
    }
  else
    {
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
catch (std::runtime_error const &e)
{
  printf ("runtime error: %s\n", e.what ());
  return EXIT_FAILURE;
}
catch (std::exception const &e)
{
  puts (e.what ());
  return EXIT_FAILURE;
}
