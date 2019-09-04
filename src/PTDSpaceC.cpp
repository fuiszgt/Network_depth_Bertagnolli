#include <RcppArmadillo.h>
#include <Rcpp.h>
// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
Rcpp::NumericVector PTDSpaceC(Rcpp::NumericMatrix data) {
  Rcpp::List dimnames = data.attr("dimnames");
  Rcpp::CharacterVector rownames = dimnames[0];
  arma::mat X = Rcpp::as<arma::mat>(data);
  int n = X.n_rows; int p = X.n_cols;
  Rcpp::NumericVector dspace(n);
  arma::mat S = arma::cov(X);
  arma::mat Sinv = arma::inv_sympd(S);
  arma::rowvec x;
  for (int i = 0; i < n; ++i) {
    // iterate over rows, each row is the point x
    x = X.row(i);
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
    dspace[i] = d.min()/n;
  }
  dspace.names() = rownames;
  return dspace;
}
