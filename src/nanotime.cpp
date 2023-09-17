
#include "RcppInt64"

//' nanotime to nanotime round-trip demo
//'
//' This function takes an nanotime-valued input vector, converts
//' it to the equivalent \code{int64_t} vector in C++, displays each
//' element after first adding one, and returns the modified vector.
//'
//' @param vec A \code{nanotime}-classed vector from R
//' @return A modified \code{nanotime} vector where each element
//' increased by one
//' @examples
//' # generate all powers of 10 fro 0 .. 18
//' if (requireNamespace("nanotime", quietly=TRUE)) {
//'     v <- nanotime::as.nanotime(10^seq(0,18))
//'     # pass them to function which will add one to each, print  and return
//'     NanotimeToNanotime(v)
//' }
// [[Rcpp::export]]
Rcpp::NumericVector NanotimeToNanotime(Rcpp::NumericVector vec) {
    std::vector<int64_t> nvec = Rcpp::fromNanotime(vec);
    for (auto& e: nvec)
        Rcpp::Rcout << ++e << std::endl;
    return Rcpp::toNanotime(nvec);
}
