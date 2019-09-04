// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double PTDepthC(arma::rowvec x, arma::mat X) {
  int n = X.n_rows; int p = X.n_cols;
  arma::mat S = arma::cov(X);
  arma::mat Sinv = arma::inv_sympd(S);
  
  for (int r = 0; r < n; ++r) {
    X.row(r) = X.row(r) - x;
  }

  arma::mat Y = X * Sinv * X.t();
  // // depth on projection lines
  arma::rowvec d(n);
  arma::rowvec m(2);

  // Modified code to fix error: no member named 'begin' in 'arma::subview_row<double>'
  arma::mat Yt = Y.t();

  for (int r = 0; r < p; ++r) {
    m[0] = std::count_if(Yt.begin_col(r), Yt.end_col(r), [](double x){return x >= 0;});
    m[1] = std::count_if(Yt.begin_col(r), Yt.end_col(r), [](double x){return x <= 0;});
    //m[0] = std::count_if(Y.row(r).begin(), Y.row(r).end(), [](double x){return x >= 0;});
    //m[1] = std::count_if(Y.row(r).begin(), Y.row(r).end(), [](double x){return x <= 0;});
    d[r] = m.min();
    // m.print("m:");
  }
  // d.print("d:");
  // min univariate depths
  return d.min()/n;
}
