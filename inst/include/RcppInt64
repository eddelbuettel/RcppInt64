
// Header-library to provide 'int64' conversion between R and C++
//
// It relies on the bit64 package and its s3 type integer64 which use
// a variable stored as 'double' to transport the int64_t type it
// represents, along with proper type casting methods.
//
// One key aspect is that the 'double' (or in Rcpp parlance the
// 'NumericVector' must carry the R class attribute so that the
// payload is taken---and interpreted---as a int64.
//
// The processing was described earlier in an Rcpp Gallery piece at
// https://gallery.rcpp.org/articles/creating-integer64-and-nanotime-vectors/
// which also details the use from the nanotime package (which also
// relies in bit64::integer64)

#include "rcppint64_bits/functions.h"
#include "rcppint64_bits/as_wrap.h"
