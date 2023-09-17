
#include "RcppInt64"

//' Integer64 to Integer64 round-trip demo
//'
//' This function takes an integer64-valued input vector, converts
//' it to the equivalent \code{int64_t} vector in C++, displays each
//' element after first adding one, and returns the modified vector.
//'
//' @param vec An \code{integer64}-classed vector from R
//' @return A modified \code{integer64} vector where each element
//' increased by one
//' @examples
//' # generate all powers of 10 fro 0 .. 18
//' if (requireNamespace("bit64", quietly=TRUE)) {
//'     v <- bit64::as.integer64(10^seq(0,18))
//'     # pass them to function which will add one to each, print  and return
//'     Int64toInt64(v)
//' }
// [[Rcpp::export]]
Rcpp::NumericVector Int64toInt64(Rcpp::NumericVector vec) {
    std::vector<int64_t> nvec = Rcpp::fromInteger64(vec);
    for (auto& e: nvec)
        Rcpp::Rcout << ++e << std::endl;
    return Rcpp::toInteger64(nvec);
}
