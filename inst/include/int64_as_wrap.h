#ifndef RCPP_INT64_AS_WRAP_H_
#define RCPP_INT64_AS_WRAP_H_

// Limited Support for as<>() and wrap()
//
// Conversion of `int64_t` (as well as std::vector<int64_t>) is
// challenging.  One reason is that R has no native type for large
// integers; its default (signed) `integer` is of size 32 bits. To
// accomate a 64 bit payload, the package `bit64` provides a clever S3
// class `integer64` that uses a 64 bit `double` to "transport" the
// bit-by-bit payload of an `int64_t` and carefully provides
// operations for it that are faithful to the 64 bit integer
// values. The package is widely used, and e.g. our `nanotime` package
// use for high(er)-precision nanosecond timestamps in R which require
// `int64_t` as the base type
//
// This generally works well with sufficient care is needed to
// transfer values. Coming from R, these _must be classed_ as
// `integer64` so that the appropriate run-time switches to the
// appropriate code can be made.
//
// Moreover, given that the "true" underlying R data type is a `double`
// it is challenging to provide a template meta-programming interface
// as _compile-time_ information is insufficient: all usage is
// contingent on _run-time_ information via the S3 class.
//
// This file offers a fairly simple interface for receiving values from
// an SEXP (i.e. R's catch-all union type) carrying an `integer64`-classed
// vector of doubles (and creating an `std::vector<int64>` from it, along
// with the inverse. Here
//    as<std::vector<int64>>(sxpvec)
// converts from an SEXP (or Rcpp::NumericVector) that must be classed
// `integer64` to a vector of `int64_t` and
//    wrap(vec)
// does the inverse to return values to R.
//
// We considered scalar support but as one cannot add an attribute to
// a C type such as `double`, one cannot "mark" values as being
// `integer64` which opens the door to accidental conversions. So this
// use is not supported here.

#include <RcppCommon.h>

namespace Rcpp {

    // non-intrusive extension via template specialisation
    template <> std::vector<int64_t> as(SEXP v);
    // maybe want scalar double too ?
    //template <> int64_t as(double);

    // non-intrusive extension via template specialisation
    template <> SEXP wrap(const std::vector<int64_t>& v);
}

#include <Rcpp.h>

// define template specialisation for as and wrap
namespace Rcpp {

    template <> std::vector<int64_t> as(SEXP s) {
        Rcpp::NumericVector v(s);
        if (!v.hasAttribute("class"))
            Rcpp::stop("Object not classed, expected S3 class 'integer64'");
        if (std::string(v.attr("class")) != "integer64")
            Rcpp::stop("Object not 'integer64' class");

        size_t len = v.size();
        std::vector<int64_t> n(len);         // storage vehicle we return them in

        // transfers values 'keeping bits' (via memcpy) but changing type
        // using reinterpret_cast would get us a warning for casting
        std::memcpy(n.data(), v.begin(), len * sizeof(double));

        return n;
    }

    template <> SEXP wrap(const std::vector<int64_t> &v) {
        size_t len = v.size();
        Rcpp::NumericVector n(len);         // storage vehicle we return them in

        // transfers values 'keeping bits' (via memcpy) but changing type
        // using reinterpret_cast would get us a warning for casting
        std::memcpy(n.begin(), v.data(), len * sizeof(double));

        // set the R class to 'integer64' so that this is not seen as a double
        n.attr("class") = "integer64";
        return n;
    }

}

#endif
