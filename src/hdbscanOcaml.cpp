// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights (to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "parlay/parallel.h"
#include "parlay/utilities.h"

#include "hdbscan/hdbscan.h"
#include "hdbscan/point.h"

extern "C" {
#define CAML_INTERNALS
#include <caml/bigarray.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <caml/alloc.h>
}

#define PAGE_SIZE 4096

extern "C" {
value hdbscan_graph_ml(value vpoints, value vmin_pts) {
  CAMLparam2(vpoints, vmin_pts);
  CAMLlocal1(result);

  const struct caml_ba_array *ba = Caml_ba_array_val(vpoints);
  assert(ba->num_dims == 2);
  assert(sizeof(double) == caml_ba_element_size[ba->flags & CAML_BA_KIND_MASK]);

  // Size of bigarray
  size_t n = ba->dim[0];
  size_t dim1 = ba->dim[1];
  size_t size = n * dim1 * sizeof(double);
  int min_pts = Int_val(vmin_pts);

  parlay::sequence<pargeo::wghEdge> output;
  if (dim1 == 2) {
    parlay::sequence<pargeo::point<2>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<2>(points, min_pts);
  } else if (dim1 == 3) {
    parlay::sequence<pargeo::point<3>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<3>(points, min_pts);
  } else if (dim1 == 4) {
    parlay::sequence<pargeo::point<4>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<4>(points, min_pts);
  } else if (dim1 == 5) {
    parlay::sequence<pargeo::point<5>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<5>(points, min_pts);
  } else if (dim1 == 6) {
    parlay::sequence<pargeo::point<6>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<6>(points, min_pts);
  } else if (dim1 == 7) {
    parlay::sequence<pargeo::point<7>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<7>(points, min_pts);
  } else if (dim1 == 8) {
    parlay::sequence<pargeo::point<8>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<8>(points, min_pts);
  } else if (dim1 == 9) {
    parlay::sequence<pargeo::point<9>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<9>(points, min_pts);
  } else if (dim1 == 10) {
    parlay::sequence<pargeo::point<10>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<10>(points, min_pts);
  } else if (dim1 == 11) {
    parlay::sequence<pargeo::point<11>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<11>(points, min_pts);
  } else if (dim1 == 12) {
    parlay::sequence<pargeo::point<12>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<12>(points, min_pts);
  } else if (dim1 == 13) {
    parlay::sequence<pargeo::point<13>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<13>(points, min_pts);
  } else if (dim1 == 14) {
    parlay::sequence<pargeo::point<14>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<14>(points, min_pts);
  } else if (dim1 == 15) {
    parlay::sequence<pargeo::point<15>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<15>(points, min_pts);
  } else if (dim1 == 16) {
    parlay::sequence<pargeo::point<16>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<16>(points, min_pts);
  } else if (dim1 == 17) {
    parlay::sequence<pargeo::point<17>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<17>(points, min_pts);
  } else if (dim1 == 18) {
    parlay::sequence<pargeo::point<18>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<18>(points, min_pts);
  } else if (dim1 == 19) {
    parlay::sequence<pargeo::point<19>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<19>(points, min_pts);
  } else if (dim1 == 20) {
    parlay::sequence<pargeo::point<20>> points(n);
    std::memcpy(points.data(), ba->data, size);
    output = pargeo::hdbscan<20>(points, min_pts);
  }

  output = parlay::sort(make_slice(output),
                        [&](pargeo::wghEdge e1, pargeo::wghEdge e2) {
                          return e1.weight < e2.weight;
                        });

  result = caml_alloc(output.size(), 0);

  for (size_t i = 0; i < output.size(); ++i) {
    value tup = caml_alloc(3, 0);
    Store_field(tup, 0, Val_int(output[i].u));
    Store_field(tup, 1, Val_int(output[i].v));
    Store_field(tup, 2, caml_copy_double(output[i].weight));
    Store_field(result, i, tup);
  }

  CAMLreturn(result);

  /*
  double *block = NULL;
  size_t block_size = output.size() * 3 * sizeof(double);

  int ret = posix_memalign((void **)&block, PAGE_SIZE, block_size);
  if (ret < 0) {
    caml_raise_out_of_memory();
  }

  parlay::parallel_for(0, output.size(), [&](size_t i) {
    block[i * 3 + 0] = static_cast<double>(output[i].u);
    block[i * 3 + 1] = static_cast<double>(output[i].v);
    block[i * 3 + 2] = output[i].weight;
  });

  CAMLreturn(
      caml_ba_alloc_dims(CAML_BA_FLOAT64 | CAML_BA_C_LAYOUT | CAML_BA_MANAGED,
                         2, block, output.size(), 3L));
  */
  /*
  parlay::sequence<pargeo::dendroNode> dendro = pargeo::dendrogram(output, n);

  double *block = NULL;
  size_t block_size = dendro.size() * 4 * sizeof(double);

  int ret = posix_memalign((void **)&block, PAGE_SIZE, block_size);
  if (ret < 0) {
    caml_raise_out_of_memory();
  }

  parlay::parallel_for(0, dendro.size(), [&](size_t i) {
    block[i * 4 + 0] = std::get<0>(dendro[i]);
    block[i * 4 + 1] = std::get<1>(dendro[i]);
    block[i * 4 + 2] = std::get<2>(dendro[i]);
    block[i * 4 + 3] = std::get<3>(dendro[i]);
  });

  CAMLreturn(
      caml_ba_alloc_dims(CAML_BA_FLOAT64 | CAML_BA_C_LAYOUT | CAML_BA_MANAGED,
                         2, block, dendro.size(), 4L));
  */
}
}
