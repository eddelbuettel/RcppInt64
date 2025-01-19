if (!requireNamespace("nanotime", quietly=TRUE)) {
    exit_file("Test needs nanotime")
}

suppressMessages({
    library(nanotime)
    library(RcppInt64)
})

Rcpp::sourceCpp("cpp/nanotime_tests.cpp")

expect_error(plusOneVector(letters[1:5]))		# cast error from character
v <- as.nanotime(10^seq(0,6))
expect_equal(plusOneVector(v), v+1)
expect_equal(plusOneVector(v[1]), v[1]+1)

v0 <- as.integer64()                            # length-0 vector
expect_equal(length(plusOneVector(v0)), 0)
expect_equivalent(class(plusOneVector(v0)), "nanotime")

expect_error(plusOneScalar("a"))				# cast error from character
expect_equal(plusOneScalar(as.nanotime(1L)),  as.nanotime(2))
expect_equal(plusOneScalar(as.nanotime(1)),   as.nanotime(2))
expect_equal(plusOneScalar(as.nanotime(-2L)), as.nanotime(-1L))
expect_equal(plusOneScalar(v[1]), v[1]+1)

expect_error(assertNanotime("a"))
expect_true(assertNanotime(as.nanotime(1)))
expect_true(assertNanotime(as.nanotime(1:5)))
