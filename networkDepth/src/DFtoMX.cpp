// [[Rcpp::depends(Rcpp)]]
#include <Rcpp.h>
using namespace Rcpp;

//[[Rcpp::export]]
NumericMatrix DFtoMX(DataFrame df) {
  int n = df.nrows();
  NumericMatrix X(n, df.size());
  for (int i = 0; i < df.size(); i++) {
    X(_, i) = NumericVector(df[i]);
  }
  return X;
}
