if (!requireNamespace("bit64", quietly=TRUE)) {
    exit_file("Test needs bit64")
}

suppressMessages({
    library(bit64)
    library(RcppInt64)
})

Rcpp::sourceCpp("cpp/int64tests.cpp")

expect_error(plusOneVector(letters[1:5]))		# cast error from character
v <- as.integer64(10^seq(0,6))
expect_equal(plusOneVector(v), v+1)
expect_equal(plusOneVector(v[1]), v[1]+1)

v0 <- as.integer64()                            # length-0 vector
expect_equal(length(plusOneVector(v0)), 0)
expect_equal(class(plusOneVector(v0)), "integer64")

expect_error(plusOneScalar("a"))				# cast error from character
expect_error(plusOneScalar(1))					# int is not integer64
expect_equal(plusOneScalar(as.integer64(1L)),  as.integer64(2))
expect_equal(plusOneScalar(as.integer64(1)),   as.integer64(2))
expect_equal(plusOneScalar(as.integer64(-2L)), as.integer64(-1L))
expect_equal(plusOneScalar(v[1]), v[1]+1)

expect_error(assertVector("a"))
#expect_error(assertVector(1L))
#expect_error(assertVector(1))
expect_true(assertVector(as.integer64(1)))
expect_true(assertVector(as.integer64(1:5)))

expect_equal(justScalar(), as.integer64(123))
