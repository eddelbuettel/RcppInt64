
suppressMessages({
    library(bit64)
    library(RcppInt64)
})

Rcpp::sourceCpp("cpp/int64tests.cpp")

expect_error(plusOneS("a"))					# cast error from character
expect_error(plusOneS(1))					# int is not integer64
expect_equal(plusOneS(as.integer64(1L)),  as.integer64(2))
expect_equal(plusOneS(as.integer64(1)),   as.integer64(2))
expect_equal(plusOneS(as.integer64(-2L)), as.integer64(-1L))

expect_error(plusOneV(letters[1:5]))		# cast error from character
v <- as.integer64(10^seq(0,6))
expect_equal(plusOneV(v), v+1)
