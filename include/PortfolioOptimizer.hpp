// PortfolioOptimizer.hpp

#ifndef PORTFOLIOOPTIMIZER_HPP
#define PORTFOLIOOPTIMIZER_HPP

#include <Eigen/Dense>
#include <vector>

class PortfolioOptimizer {
public:
    // Constructor
    PortfolioOptimizer(const Eigen::VectorXd &meanReturns,
                       const Eigen::MatrixXd &covMatrix,
                       double riskFreeRate);

    // Method to set constraints, for example, the sum of weights equals 1
    void setConstraints(const Eigen::VectorXd &constraints);

    // Perform the optimization to find the portfolio with the maximum Sharpe ratio
    void optimizeForSharpeRatio();

    // Get the optimal weights after optimization
    Eigen::VectorXd getOptimalWeights() const;

    // Get the expected return of the optimized portfolio
    double getExpectedReturn() const;

    // Get the expected volatility of the optimized portfolio
    double getExpectedVolatility() const;

    // Get the Sharpe ratio of the optimized portfolio
    double getSharpeRatio() const;

private:
    Eigen::VectorXd meanReturns_; // Expected returns for each asset
    Eigen::MatrixXd covMatrix_;   // Covariance matrix for the assets
    Eigen::VectorXd weights_;     // Asset weights for the optimized portfolio
    double riskFreeRate_;         // The risk-free rate
    Eigen::VectorXd constraints_; // Constraints for the optimization problem

    // Private method to calculate the Sharpe ratio
    double calculateSharpeRatio(const Eigen::VectorXd &weights) const;
};

#endif // PORTFOLIOOPTIMIZER_HPP
