#include "Statistics.h"
#include <cmath>

// Calculating daily returns
Eigen::MatrixXd Statistics::calculateReturns(const Eigen::MatrixXd& prices) {
    Eigen::MatrixXd returns = Eigen::MatrixXd(prices.rows() - 1, prices.cols());
    for (int i = 1; i < prices.rows(); ++i) {
        returns.row(i - 1) = (prices.row(i) - prices.row(i - 1)).cwiseQuotient(prices.row(i - 1));
    }
    return returns;
}

// Calculating Mean daily returns
Eigen::VectorXd Statistics::meanDailyReturns(const Eigen::MatrixXd& returns) {
    return returns.colwise().mean();
}

// Calculating Covariance of daily returns
Eigen::MatrixXd Statistics::covarianceMatrix(const Eigen::MatrixXd& returns) {
    int n = returns.rows();
    Eigen::MatrixXd centered = returns.rowwise() - returns.colwise().mean();
    return (centered.adjoint() * centered) / double(n - 1);
}

// Calculating Volatility (Standard Deviation) of daily returns
Eigen::VectorXd Statistics::volatility(const Eigen::MatrixXd& returns) {
    Eigen::MatrixXd centered = returns.rowwise() - returns.colwise().mean();
    return (centered.array().square().colwise().sum() / double(returns.rows() - 1)).sqrt();
}