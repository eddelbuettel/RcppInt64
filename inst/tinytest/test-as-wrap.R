if (!requireNamespace("bit64", quietly=TRUE)) {
    exit_file("Test needs bit64")
}

suppressMessages({
    library(bit64)
    library(RcppInt64)
})

Rcpp::sourceCpp("cpp/int64_as_wrap.cpp")

expect_error(plusOneNumericVector(letters[1:5]))		# cast error from character
v <- as.integer64(10^seq(0,6))
expect_equal(plusOneNumericVector(v), v+1) 				# whole vector
expect_equal(plusOneNumericVector(v[1]), v[1]+1)		# single (first) element


expect_error(plusOneSEXP("a"))					# cast error from character
expect_error(plusOneSEXP(1))					# int is not integer64
expect_equal(plusOneSEXP(as.integer64(1L)),  as.integer64(2))
expect_equal(plusOneSEXP(as.integer64(1)),   as.integer64(2))
expect_equal(plusOneSEXP(as.integer64(-2L)), as.integer64(-1L))
expect_equal(plusOneSEXP(v), v+1) 				# SEXP does vector too
