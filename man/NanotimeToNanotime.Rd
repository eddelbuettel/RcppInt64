% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{NanotimeToNanotime}
\alias{NanotimeToNanotime}
\title{nanotime to nanotime round-trip demo}
\usage{
NanotimeToNanotime(vec)
}
\arguments{
\item{vec}{A \code{nanotime}-classed vector from R}
}
\value{
A modified \code{nanotime} vector where each element
increased by one
}
\description{
This function takes an nanotime-valued input vector, converts
it to the equivalent \code{int64_t} vector in C++, displays each
element after first adding one, and returns the modified vector.
}
\examples{
# generate all powers of 10 fro 0 .. 18
if (requireNamespace("nanotime", quietly=TRUE)) {
    v <- nanotime::as.nanotime(10^seq(0,18))
    # pass them to function which will add one to each, print  and return
    NanotimeToNanotime(v)
}
}
