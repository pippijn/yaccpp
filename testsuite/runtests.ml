(* +=====~~~-------------------------------------------------------~~~=====+ *)
(* |                          Test suite description                       | *)
(* +=====~~~-------------------------------------------------------~~~=====+ *)

TestFramework.(run "testsuite" [
  { empty with
    tool = "yaccpp";
    suffixes = [".y"; ".yy"];
    dirs = [
      "yaccpp";
    ];
  };
])
