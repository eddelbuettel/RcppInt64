
#include <RcppInt64>

// [[Rcpp::depends(RcppInt64)]]

/* Assume an integer64 object already is allocated */
static inline uint64_t *NumericVector_as_uint64_t(Rcpp::NumericVector vec) {
    return (uint64_t *)((void *)vec.begin());
}

/* Allocate an integer64 object */
static inline Rcpp::NumericVector Integer64(size_t size) {
    Rcpp::NumericVector n(size);
    n.attr("class") = "integer64";
    return n;
}

// [[Rcpp::export]]
Rcpp::NumericVector Int64toInt64timesTwoPlusOne(Rcpp::NumericVector vec) {
    Rcpp::NumericVector ret = Integer64(vec.size());
    uint64_t *vec64 = NumericVector_as_uint64_t(vec);
    uint64_t *ret64 = NumericVector_as_uint64_t(ret);

    for (size_t i = 0; i < ret.size(); ++i) {
        ret64[i] = vec64[i] * 2 + 1;
        // Rcpp::Rcout << ++ret64[i] << std::endl;
    }
    return ret;
}


/*** R
v <- as.integer64(c(1e0, 1e3, 1e6, 1e9, 1e12, 1e15, 1e18))
v
sum(v)
Int64toInt64timesTwoPlusOne(v)
***/
