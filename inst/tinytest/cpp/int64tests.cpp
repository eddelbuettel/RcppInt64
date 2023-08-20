
#include "RcppInt64.h"

// [[Rcpp::depends(RcppInt64)]]

// [[Rcpp::export]]
Rcpp::NumericVector plusOneVector(Rcpp::NumericVector vec) {
    std::vector<int64_t> nvec = Rcpp::fromInteger64(vec);
    for (auto& elem: nvec) elem++;
    return Rcpp::toInteger64(nvec);
}

// [[Rcpp::export]]
Rcpp::NumericVector plusOneScalar(SEXP scl) {
    Rcpp::NumericVector v(scl);
    if (!isInteger64(v)) Rcpp::stop("Expecting 'integer64'");
    int64_t val = Rcpp::fromInteger64(Rcpp::as<double>(scl));
    return Rcpp::toInteger64(++val);
}

// [[Rcpp::export]]
bool assertVector(SEXP sxp) {
    return Rcpp::isInteger64(sxp);
}
