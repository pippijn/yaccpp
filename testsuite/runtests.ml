(* +=====~~~-------------------------------------------------------~~~=====+ *)
(* |                          Test suite description                       | *)
(* +=====~~~-------------------------------------------------------~~~=====+ *)

TestFramework.(run "testsuite" [
  {
    tool = "yaccpp";
    suffixes = [".y"; ".yy"];
    options = None;
    dirs = [
      "yaccpp";
    ];
  };
])
