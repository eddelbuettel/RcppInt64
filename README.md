
## RcppInt64: Passing integer64 and nanotime To And From C++

[![CI](https://github.com/eddelbuettel/RcppInt64/actions/workflows/r2u.yaml/badge.svg)](https://github.com/eddelbuettel/RcppInt64/actions/workflows/r2u.yaml)
[![License](https://eddelbuettel.github.io/badges/GPL2+.svg)](https://www.gnu.org/licenses/gpl-2.0.html)
[![CRAN](https://www.r-pkg.org/badges/version/RcppInt64)](https://cran.r-project.org/package=RcppInt64)
[![Dependencies](https://tinyverse.netlify.com/badge/RcppInt64)](https://cran.r-project.org/package=RcppInt64)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rcppint64)](https://github.com/eddelbuettel/rcppint64)

### Motivation

While R has no _native_ support for 64-bit integer values, the [`bit64`
package](https://cran.r-project.org/package=bit64) by Jens Oehlschlägel is widely used to fill this
gap by (very carefully) passing the bitmaps of `int64_t` values around in `double`.  This works on
the R side by virtue of a S3 class `integer64` with proper dispatching, and on the C/C++ side where
the values can be past by `memcpy`.  What one cannot do is simply copying or casting: the tradeoff
made in representing a `double` with as large a range is that the 'delta' between values is not
constant acros the range and naive casting between both representation *will* be lossy and distort
values.

This package contains helper functions that were previously appearing in helper header files in
different packages, and reorganizes them along with a proper unit tests.  The key header file
provided here can be included directly. Function to assert `integer64` source, convert to and from
in both scalar and vector cases as well as a pair of `as<>()` and `wrap()` converters are provided.

As our [nanotime package]() builds on the same `integer64` infrastructure, its bi-directional
conversions between R and C++ are also supported.

## Examples

### Int64

The example for the included demonstration function show how a vector of
`integer64` values (here spanning the power of 10 ranging from 0 to 18)
can be received in C++, altered (where we just add one) and returned, all
while maintaining `integer64` aka `int64_t` type.

```r
> example(Int64toInt64)

I64I64> # generate all powers of 10 fro 0 .. 18
I64I64> v <- bit64::as.integer64(10^seq(0,18))

I64I64> # pass them to function which will add one to each, print  and return
I64I64> Int64toInt64(v)
2
11
101
1001
10001
100001
1000001
10000001
100000001
1000000001
10000000001
100000000001
1000000000001
10000000000001
100000000000001
1000000000000001
10000000000000001
100000000000000001
1000000000000000001
integer64
 [1] 2                   11                  101
 [4] 1001                10001               100001
 [7] 1000001             10000001            100000001
[10] 1000000001          10000000001         100000000001
[13] 1000000000001       10000000000001      100000000000001
[16] 1000000000000001    10000000000000001   100000000000000001
[19] 1000000000000000001
>
```

### Nanotime

Similarly, we can instantiate a vector of `nanotime` values and increment, show, and return its
values.

```r
> example(NanotimeToNanotime)

NntmTN> # generate all powers of 10 fro 0 .. 18
NntmTN> if (requireNamespace("nanotime", quietly=TRUE)) {
NntmTN+     v <- nanotime::as.nanotime(10^seq(0,18))
NntmTN+     # pass them to function which will add one to each, print  and return
NntmTN+     NanotimeToNanotime(v)
NntmTN+ }
2
11
101
1001
10001
100001
1000001
10000001
100000001
1000000001
10000000001
100000000001
1000000000001
10000000000001
100000000000001
1000000000000001
10000000000000001
100000000000000001
1000000000000000001
 [1] 1970-01-01T00:00:00.000000002+00:00 1970-01-01T00:00:00.000000011+00:00
 [3] 1970-01-01T00:00:00.000000101+00:00 1970-01-01T00:00:00.000001001+00:00
 [5] 1970-01-01T00:00:00.000010001+00:00 1970-01-01T00:00:00.000100001+00:00
 [7] 1970-01-01T00:00:00.001000001+00:00 1970-01-01T00:00:00.010000001+00:00
 [9] 1970-01-01T00:00:00.100000001+00:00 1970-01-01T00:00:01.000000001+00:00
[11] 1970-01-01T00:00:10.000000001+00:00 1970-01-01T00:01:40.000000001+00:00
[13] 1970-01-01T00:16:40.000000001+00:00 1970-01-01T02:46:40.000000001+00:00
[15] 1970-01-02T03:46:40.000000001+00:00 1970-01-12T13:46:40.000000001+00:00
[17] 1970-04-26T17:46:40.000000001+00:00 1973-03-03T09:46:40.000000001+00:00
[19] 2001-09-09T01:46:40.000000001+00:00
>
```

### Installation

The package is available via [CRAN](https://cran.r-project.org) and can be installed the usual way
via `install.packages("RcppInt64")`.

### Contributing

Any problems, bug reports, or features requests for the package can be submitted and handled most
conveniently as [Github issues](https://github.com/eddelbuettel/rcppint64/issues) in the
repository.

Before submitting pull requests, it is frequently preferable to first discuss need and scope in such
an issue ticket.  See the file
[Contributing.md](https://github.com/RcppCore/Rcpp/blob/master/Contributing.md) (in the
[Rcpp](https://github.com/RcppCore/Rcpp) repo) for a brief discussion.

### Author

Dirk Eddelbuettel

### License

GPL (>= 2)
