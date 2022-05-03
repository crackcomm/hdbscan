(* Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights (to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. *)

open Core
open Bigarray

type arr = (float, float64_elt, c_layout) Array2.t
type edges = (int * int * float) array [@@deriving sexp]

external graph : arr -> int -> edges = "hdbscan_graph_ml"

let graph ~min_pts points = graph points min_pts

let%expect_test "graph" =
  let input =
    Array2.of_array
      Float64
      c_layout
      [| [| 1.1; 2.3 |]
       ; [| 1.2; 2.2 |]
       ; [| 1.4; 1.9 |]
       ; [| 2.3; 1.1 |]
       ; [| 2.2; 1.2 |]
       ; [| 1.9; 1.4 |]
       ; [| 3.11; 3.40 |]
       ; [| 3.10; 3.41 |]
       ; [| 3.13; 3.43 |]
      |]
  in
  let out = graph ~min_pts:3 input in
  print_s [%sexp (out : edges)];
  (* Output from Python library. *)
  [%expect
    {|
    ((6 7 0.036055512754640105) (7 8 0.036055512754640105)
     (0 1 0.49999999999999983) (1 2 0.49999999999999983)
     (4 5 0.49999999999999983) (3 4 0.49999999999999983)
     (2 5 0.70710678118654757) (1 7 2.25257630281418)) |}]
;;
