#include "config.h"

#include "lexer.h"
#include "parser.h"
#include "printer.h"
#include "sighandler.h"

#include <algorithm>
#include <clocale>
#include <cstdlib>

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
      puts ("usage: jmlc <jmlfile>");
      return EXIT_SUCCESS;
    }

  std::vector<std::string> files (argv + 1, argv + argc);;
  std::sort (files.begin (), files.end ());

#if 0
  std::copy (files.begin (), files.end (), std::ostream_iterator<std::string> (std::cout, "\n"));
#endif

  lexer lex (files);
  parser parse (lex);

  if (node_ptr doc = parse ())
    {
      printer prn;
      doc->accept (prn);
    }
  else
    {
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
catch (std::exception const &e)
{
  printf ("error: %s\n", e.what ());
  return EXIT_FAILURE;
}
