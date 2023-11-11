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

// Calculating Volatility (standard deviation)
Eigen::VectorXd Statistics::volatility(const Eigen::MatrixXd& returns) {
    return (returns.rowwise() - returns.colwise().mean()).array().square().colwise().sum().sqrt() / sqrt(returns.rows());
}

// Calculating Correlation matrix
Eigen::MatrixXd Statistics::correlationMatrix(const Eigen::MatrixXd& returns) {
    Eigen::MatrixXd cov = covarianceMatrix(returns);
    Eigen::VectorXd std_dev = volatility(returns);

    Eigen::MatrixXd corrMatrix = Eigen::MatrixXd(cov.rows(), cov.cols());

    for (int i = 0; i < cov.rows(); ++i) {
        for (int j = 0; j < cov.cols(); ++j) {
            cov(i, j) = cov(i, j) / (std_dev(i) * std_dev(j));
        }
    }
    return corrMatrix;
}

// =====================================================

// Portfolio Expected Return
double Statistics::portfolioExpectedReturn(const Eigen::VectorXd& weights, const Eigen::VectorXd& meanReturns) {
    return weights.dot(meanReturns);
}

// Portfolio Variance
double Statistics::portfolioVariance(const Eigen::VectorXd& weights, const Eigen::MatrixXd& covMatrix) {
    return weights.transpose() * covMatrix * weights;
}

// Portfolio Standard Deviation (Volatility)
double Statistics::portfolioStandardDeviation(const Eigen::VectorXd& weights, const Eigen::MatrixXd& covMatrix) {
    return std::sqrt(portfolioVariance(weights, covMatrix));
}

// Portfolio Sharpe Ratio
double Statistics::portfolioSharpeRatio(const Eigen::VectorXd& weights, const Eigen::VectorXd& meanReturns, const Eigen::MatrixXd& covMatrix, double riskFreeRate) {
    double expectedReturn = portfolioExpectedReturn(weights, meanReturns);
    double volatility = portfolioStandardDeviation(weights, covMatrix);
    return (expectedReturn - riskFreeRate) / volatility;
}
