#include "include/PortfolioOptimizer.h"
// #include <QuantLib/QuantLib.hpp>

PortfolioOptimizer::PortfolioOptimizer(const Eigen::VectorXd &meanReturns,
                                       const Eigen::MatrixXd &covMatrix,
                                       double riskFreeRate)
    : meanReturns_(meanReturns), covMatrix_(covMatrix), riskFreeRate_(riskFreeRate) {
    // Initially, set weights to equal distribution or another starting guess
    weights_ = Eigen::VectorXd::Constant(meanReturns.size(), 1.0 / meanReturns.size());
}

void PortfolioOptimizer::setConstraints(const Eigen::VectorXd &constraints) {
    constraints_ = constraints;
}

void PortfolioOptimizer::optimizeForSharpeRatio() {
    // Here we would define the optimization problem
    // This would involve setting up the objective function to maximize the Sharpe ratio
    // And adding any constraints necessary - such as the weights summing to 1

    // For illustration, let's say we use a QuantLib optimizer, the process would look like:
    // QuantLib::OptimizationProblem problem(...);
    // QuantLib::OptimizationMethod method(...);
    // method.solve(problem);

    // For now, let's just assign some dummy values to the weights
    weights_ = Eigen::VectorXd::Random(meanReturns_.size()).cwiseAbs(); // Random positive weights
    weights_ /= weights_.sum(); // Normalize so that they sum up to 1
}

Eigen::VectorXd PortfolioOptimizer::getOptimalWeights() const {
    return weights_;
}

double PortfolioOptimizer::getExpectedReturn() const {
    return weights_.dot(meanReturns_);
}

double PortfolioOptimizer::getExpectedVolatility() const {
    return std::sqrt(weights_.transpose() * covMatrix_ * weights_);
}

double PortfolioOptimizer::getSharpeRatio() const {
    return calculateSharpeRatio(weights_);
}

double PortfolioOptimizer::calculateSharpeRatio(const Eigen::VectorXd &weights) const {
    double portfolioReturn = weights.dot(meanReturns_);
    double portfolioVolatility = std::sqrt(weights.transpose() * covMatrix_ * weights);
    return (portfolioReturn - riskFreeRate_) / portfolioVolatility;
}
