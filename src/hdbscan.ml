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

open Bigarray

type arr = (float, float64_elt, c_layout) Array2.t

external hdbscan_graph : arr -> int -> arr = "hdbscan_graph_ml"

let hdbscan_graph ~min_pts points = hdbscan_graph points min_pts

let%expect_test "hdbscan_graph" =
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
  let print_ba ba =
    let open Core in
    let len1 = Array2.dim1 ba - 1 in
    let print_dim2 i1 =
      if i1 = 0 then printf "[" else printf " [";
      let len = Array2.dim2 ba - 1 in
      for i2 = 0 to len do
        if i2 = len
        then
          if i1 = len1
          then printf "%.4f]]\n" ba.{i1, i2}
          else printf "%.4f]\n" ba.{i1, i2}
        else printf "%.4f " ba.{i1, i2}
      done
    in
    printf "[";
    for i1 = 0 to len1 do
      print_dim2 i1
    done
  in
  let out = hdbscan_graph ~min_pts:3 input in
  print_ba out;
  (* Output from Python library. *)
  [%expect
    {|
    [[6.0000 7.0000 0.0361]
     [7.0000 8.0000 0.0361]
     [0.0000 1.0000 0.5000]
     [1.0000 2.0000 0.5000]
     [4.0000 5.0000 0.5000]
     [3.0000 4.0000 0.5000]
     [2.0000 5.0000 0.7071]
     [1.0000 7.0000 2.2526]] |}]
;;
