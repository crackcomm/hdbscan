(lang dune 2.7)

(formatting
 (enabled_for ocaml))

(authors "\197\129ukasz Kurowski")

(maintainers "crackcomm@gmail.com")

(generate_opam_files true)

(package
 (name hdbscan)
 (synopsis "HDBSCAN Clustering")
 (description "A Fast Parallel Algorithm for HDBSCAN* Clustering")
 (depends
  (core
   (>= 0.15.0))
  (ppx_jane
   (>= 0.15.0))
  (ocaml
   (>= 4.14.0))))
