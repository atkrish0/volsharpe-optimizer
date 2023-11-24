#include "PortfolioOptimizer.h"

// Generates random weights for portfolio
std::vector<double> PortfolioOptimizer::generateRandomWeights(int numStocks) {
    std::vector<double> weights(numStocks);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    double sum = 0.0;
    for (int i = 0; i < numStocks; ++i) {
        weights[i] = dis(gen);
        sum += weights[i];
    }

    // Normalize the weights so they sum to 1
    for (double &weight : weights) {
        weight /= sum;
    }

    return weights;
}

// Calculates the return of the portfolio
double PortfolioOptimizer::calculatePortfolioReturn(const Eigen::VectorXd& meanReturns,
                                                    const std::vector<double>& weights) {
    double portfolioReturn = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        portfolioReturn += meanReturns[i] * weights[i];
    }
    return portfolioReturn * 252; // Assuming 252 trading days in a year
}

// Calculates the volatility of the portfolio
double PortfolioOptimizer::calculatePortfolioVolatility(const Eigen::MatrixXd& covMatrix,
                                                        const std::vector<double>& weights) {
    Eigen::VectorXd w = Eigen::Map<const Eigen::VectorXd>(weights.data(), weights.size());
    double volatility = std::sqrt(w.transpose() * covMatrix * w);
    return volatility * std::sqrt(252); // Annualizing the volatility
}

// Optimizes the portfolio over a number of random allocations
std::vector<PortfolioResult> PortfolioOptimizer::optimizePortfolio(const Eigen::VectorXd& meanReturns,
                                                                   const Eigen::MatrixXd& covMatrix,
                                                                   int numPortfolios, int numStocks) {
    std::vector<PortfolioResult> results;
    for (int i = 0; i < numPortfolios; ++i) {
        std::vector<double> w = generateRandomWeights(numStocks);
        double portfolioReturn = calculatePortfolioReturn(meanReturns, w);
        double portfolioVol = calculatePortfolioVolatility(covMatrix, w);
        double sharpeRatio = portfolioReturn / portfolioVol;
        results.push_back({portfolioReturn, portfolioVol, sharpeRatio, w});
    }
    return results;
}
