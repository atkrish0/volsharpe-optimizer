#ifndef PORTFOLIOOPTIMIZER_H
#define PORTFOLIOOPTIMIZER_H

#include <Eigen/Dense>
#include <vector>
#include <random>

struct PortfolioResult {
    double return_;
    double volatility;
    double sharpeRatio;
    std::vector<double> weights;
};

class PortfolioOptimizer {
public:
    static std::vector<PortfolioResult> optimizePortfolio(const Eigen::VectorXd& meanReturns,
                                                          const Eigen::MatrixXd& covMatrix,
                                                          int numPortfolios, int numStocks);

private:
    static std::vector<double> generateRandomWeights(int numStocks);
    static double calculatePortfolioReturn(const Eigen::VectorXd& meanReturns,
                                           const std::vector<double>& weights);
    static double calculatePortfolioVolatility(const Eigen::MatrixXd& covMatrix,
                                               const std::vector<double>& weights);
};

#endif // PORTFOLIOOPTIMIZER_H
