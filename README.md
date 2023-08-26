
## RcppInt64: Rcpp Bindings for Passing integer64 Variables To And From C++

[![CI](https://github.com/eddelbuettel/RcppInt64/actions/workflows/r2u.yaml/badge.svg)](https://github.com/eddelbuettel/RcppInt64/actions/workflows/r2u.yaml)
[![License](https://eddelbuettel.github.io/badges/GPL2+.svg)](https://www.gnu.org/licenses/gpl-2.0.html)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rcppint64)](https://github.com/eddelbuettel/rcppint64)
<!-- [![CRAN](https://www.r-pkg.org/badges/version/Rcppint64)](https://cran.r-project.org/package=Rcppint64) -->
<!-- [![Dependencies](https://tinyverse.netlify.com/badge/Rcppint64)](https://cran.r-project.org/package=Rcppint64) -->

### Motivation

While has no _native_ support for 64-bit integer values, the [`bit64`
package](https://cloud.r-project.org/web/packages/bit64/index.html) by Jens Oehlschlägel is widely
used to fill this gap by (very carefully) passing the bitmaps of `int64_t` values around in
`double`.  This works on the R side by virtue of a S3 call `integer64`, on the C/C++ side the values
can be past by `memcpy`.   What one cannot do is simply copying or casting: the tradeoff made in
representing a `double` with as large a range is that the 'delta' between values is not constant
acros the range and naive casting between both representation *will* be lossy and distort values.

This package contains a handful of very simple helper functions previously floating around in helper
header files in different packages, and reorganizes them along with a few proper unit tests.  The
header provided here can be included directly.

## Example

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
