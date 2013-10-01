install Program ".DEFAULT" [
  (* Target *)
  Name		"yaccpp";

  Sources [
    "phases/anon_rules.cpp";
    "phases/call_macros.cpp";
    "phases/cardinality.cpp";
    "phases/insert_syms.cpp";
    "phases/nop.cpp";
    "phases/print.cpp";
    "phases/resolve_refs.cpp";
    "phases/scobind.cpp";
    "phases/xmlprint.cpp";
    "exception.cpp";
    "lexer.cpp";
    "main.cpp";
    "make_token.cpp";
    "node.cpp";
    "parser.cpp";
    "phases.cpp";
    "sighandler.cpp";
    "symtab.cpp";
    "token.cpp";
    "visitor.cpp";
    "yylex.lpp";
    "yyparse.ypp";
  ];

  Headers [
    "phases/is_ref.h";
    "exception.h";
    "lexer.h";
    "local.h";
    "node.h";
    "node_ptr.h";
    "object_pool.h";
    "parser.h";
    "phase.h";
    "phases.h";
    "symtab.h";
    "visitor.h";
    "y.tab.h";
    "ylcode.h";
    "yyparse.hpp";
    "yylex.hpp";
  ];

  Var ("OM_YFLAGS", "-d");
  Var ("OM_CPPFLAGS", "-I$(dir .)");

  Recurse ("phases");
]
