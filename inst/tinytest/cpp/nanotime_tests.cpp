
#include "RcppInt64"

// [[Rcpp::depends(RcppInt64)]]

// [[Rcpp::export]]
Rcpp::NumericVector plusOneVector(Rcpp::NumericVector vec) {
    std::vector<int64_t> nvec = Rcpp::fromNanotime(vec);
    for (auto& elem: nvec) elem++;
    return Rcpp::toNanotime(nvec);
}

// [[Rcpp::export]]
Rcpp::NumericVector plusOneScalar(SEXP scl) {
    Rcpp::NumericVector v(scl);
    if (!isNanotime(v)) Rcpp::stop("Expecting 'nanotime'");
    int64_t val = Rcpp::fromNanotime(Rcpp::as<double>(scl));
    return Rcpp::toNanotime(++val);
}

// [[Rcpp::export]]
bool assertNanotime(SEXP sxp) {
    return Rcpp::isNanotime(sxp);
}
