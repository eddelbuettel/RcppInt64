
#include "int64_as_wrap.h"

// [[Rcpp::depends(RcppInt64)]]

// [[Rcpp::export]]
Rcpp::NumericVector plusOneNumericVector(Rcpp::NumericVector vec) {
    std::vector<int64_t> nvec = Rcpp::as<std::vector<int64_t>>(vec);
    for (auto& elem: nvec) elem++;
    return Rcpp::wrap(nvec);
}

// [[Rcpp::export]]
Rcpp::NumericVector plusOneSEXP(SEXP sxp) {
    std::vector<int64_t> nvec = Rcpp::as<std::vector<int64_t>>(sxp);
    for (auto& elem: nvec) elem++;
    return Rcpp::wrap(nvec);
}
