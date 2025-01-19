// Header-library to provide 'int64' (and 'nanotime') conversion
// between R and C++
//
// It relies on the bit64 package and its s3 type integer64 which use
// a variable stored as 'double' to transport the int64_t type it
// represents, along with proper type casting methods.
//
// One key aspect is that the 'double' (or in Rcpp parlance the
// 'NumericVector' must carry the R class attribute so that the
// payload is taken---and interpreted---as a int64.
//
// The processing was described earlier in an Rcpp Gallery piece at
// https://gallery.rcpp.org/articles/creating-integer64-and-nanotime-vectors/
// which also details the use from the nanotime package (which also
// relies in bit64::integer64)

// Additional helper to assert integer64 source, and conversion to and
// from for both vector and scalar cases

#pragma once

#include <Rcpp/Lightest>
#include <cstdint>              		// for int64_t

namespace Rcpp {

//
// Assertion
//

// Check for integer64 type -- which for R 'S3' object means checking the attributes
inline bool isInteger64(Rcpp::NumericVector v) {
    if (!v.hasAttribute("class")) {
        return FALSE;
    }
    std::string s = v.attr("class");
    return s == "integer64";
}

// cannot easily do the scalar case as the 'double' is a plain old datatype
// that cannot carry a class attribute as an R SEXP (and hence Rcpp type) could


//
// C++ int64_t payload to R integer64 payload
//

// Convert from an C++ int64_t vector to an R 'integer64' vector
inline Rcpp::NumericVector toInteger64(const std::vector<int64_t>& v) {
    size_t len = v.size();
    Rcpp::NumericVector n(len);         // storage vehicle we return them in

    // transfers values 'keeping bits' (via memcpy) but changing type
    // using reinterpret_cast would get us a warning for casting
    if (len > 0)
        std::memcpy(n.begin(), v.data(), len * sizeof(double));

    // set the R class to 'integer64' so that this is not seen as a double
    n.attr("class") = "integer64";
    return n;
}

// Convert from an C++ int64_t scalar to an R 'integer64' scalar
inline Rcpp::NumericVector toInteger64(const int64_t& v) {
    Rcpp::NumericVector n(1);
    // transfers values 'keeping bits' (via memcpy) but changing type
    // using reinterpret_cast would get us a warning for casting
    std::memcpy(n.begin(), &v, sizeof(double));

    // set the R class to 'integer64' so that this is not seen as a double
    n.attr("class") = "integer64";
    return n;
}


//
// R integer64 payload to C++ int64_t payload
//

// Convert from an C++ int64_t vector to an R 'integer64' vector
inline std::vector<int64_t> fromInteger64(Rcpp::NumericVector v, bool check = true) {
    if (check && !isInteger64(v))
        Rcpp::stop("Incoming argument 'v' should be an integer64 type");

    size_t len = v.size();
    std::vector<int64_t> n(len);         // storage vehicle we return them in

    // transfers values 'keeping bits' (via memcpy) but changing type
    // using reinterpret_cast would get us a warning for casting
    if (len > 0)
        std::memcpy(n.data(), v.begin(), len * sizeof(double));

    return n;
}


// Convert a scalar 'double' (ie R 'integer64') to a scalar int64_t
// Note that this method CANNOT test if the incoming value is a 'integer64' as we cannot
// attach an S3 class attribute to a double -- so consider the next method using a SEXP
inline int64_t fromInteger64(const double val) {
    // cannot but really should check val for class
    int64_t newval;
    memcpy(&newval, &val, sizeof(double));
    return newval;
}

// Convert a scalar 'double' (ie R 'integer64') to a scalar int64_t
inline int64_t fromInteger64(SEXP val) {
    // could check for length 1 here
    Rcpp::NumericVector v(val);
    if (!isInteger64(v)) Rcpp::stop("Expecting 'integer64'");

    // cannot but really should check val for class
    int64_t newval;
    memcpy(&newval, v.begin(), sizeof(double));
    return newval;
}


// Check for nanotime type -- which for R object means checking the attributes
inline bool isNanotime(Rcpp::NumericVector v) {
    if (!v.hasAttribute("class")) {
        return FALSE;
    }
    std::string c = v.attr("class");
    std::string s = v.attr(".S3Class");
    return c == "nanotime" && s == "integer64";
}


// Create a nanotime object (an S4 class object) by invoking an
// existing R macro along with proper class attributes.
inline Rcpp::NumericVector toNanotime(const std::vector<int64_t>& v) {
    size_t len = v.size();
    Rcpp::NumericVector n(len);
    if (len > 0)
        std::memcpy(n.begin(), v.data(), len * sizeof(double));

    Rcpp::CharacterVector cl = Rcpp::CharacterVector::create("nanotime");
    cl.attr("package") = "nanotime";

    Rf_asS4(n, TRUE, FALSE);
    n.attr(".S3Class") = "integer64";
    n.attr("class") = cl;

    return(n);
}

// Create a nanotime (scalar) object (an S4 class object)
inline Rcpp::NumericVector toNanotime(const int64_t& v) {
    Rcpp::NumericVector n(1);
    // transfers values 'keeping bits' (via memcpy) but changing type
    // using reinterpret_cast would get us a warning for casting
    std::memcpy(n.begin(), &v, sizeof(double));

    Rcpp::CharacterVector cl = Rcpp::CharacterVector::create("nanotime");
    cl.attr("package") = "nanotime";

    Rf_asS4(n, TRUE, FALSE);
    n.attr(".S3Class") = "integer64";
    n.attr("class") = cl;

    return(n);
}


// Convert from an C++ int64_t vector to an R 'integer64' vector
inline std::vector<int64_t> fromNanotime(Rcpp::NumericVector v, bool check = true) {
    if (check && !isNanotime(v))
        Rcpp::stop("Incoming argument 'v' should be a 'nanotime' type");

    size_t len = v.size();
    std::vector<int64_t> n(len);         // storage vehicle we return them in

    // transfers values 'keeping bits' (via memcpy) but changing type
    // using reinterpret_cast would get us a warning for casting
    if (len > 0)
        std::memcpy(n.data(), v.begin(), len * sizeof(double));

    return n;
}

// Convert a scalar nanotime 'double' (ie R 'integer64') to a scalar int64_t
inline int64_t fromNanotime(const double val) {
    // cannot but really should check val for class
    int64_t newval;
    memcpy(&newval, &val, sizeof(double));
    return newval;
}

// Convert a scalar 'double' (ie R 'integer64') to a scalar int64_t
inline int64_t fromNanotime(SEXP val) {
    // could check for length 1 here
    Rcpp::NumericVector v(val);
    if (!isNanotime(v)) Rcpp::stop("Expecting 'nanotime'");

    // cannot but really should check val for class
    int64_t newval;
    memcpy(&newval, v.begin(), sizeof(double));
    return newval;
}


}
