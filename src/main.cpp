#include <iostream>
#include <iomanip>
#include "DataHandler.h"
#include "Statistics.h"
#include "PortfolioOptimizer.h"
#include "MaxSharpePortfolio.h"
#include "MinVolatilityPortfolio.h"

using namespace std;

int main() {

    // Read stock prices from CSV
    std::string filePath = "/Users/atheeshkrishnan/AK/DEV/OOP1/rutgersmqf-portfolio-optimization/data/portfolio.csv";
    int numberOfRows = 494; 
    int numberOfColumns = 5; 
    Eigen::MatrixXd portfolio = DataHandler::readCSV(filePath);

    // Calculate daily returns, mean returns, etc. as before
    Eigen::MatrixXd returns = Statistics::calculateReturns(portfolio);
    Eigen::VectorXd meanReturns = Statistics::meanDailyReturns(returns);
    Eigen::MatrixXd covMatrix = Statistics::covarianceMatrix(returns);
    Eigen::VectorXd volatility = Statistics::volatility(returns);

    // Output stats
    std::cout << "Mean Daily Returns:\n" << meanReturns << "\n\n";
    std::cout << "Covariance Matrix:\n" << covMatrix << "\n\n";
    std::cout << "Volatility:\n" << volatility << "\n\n";

    // Set the number of random portfolio weights to generate
    int numPortfolios = 1000000;
    std::vector<PortfolioResult> optimizedPortfolios = PortfolioOptimizer::optimizePortfolio(
        meanReturns, covMatrix, numPortfolios, numberOfColumns);

    // Strategy Execution
    MaxSharpePortfolio maxSharpeStrategy;
    MinVolatilityPortfolio minVolStrategy;

    PortfolioResult maxSharpePortfolio = maxSharpeStrategy.executeStrategy(optimizedPortfolios);
    PortfolioResult minVolatilityPortfolio = minVolStrategy.executeStrategy(optimizedPortfolios);

    // Output the weights for the maximized Sharpe ratio portfolio
    std::cout << "\nMaximized Sharpe Ratio Portfolio:" << std::endl;
    std::cout << "Weights: ";
    for (const auto& weight : maxSharpePortfolio.weights) {
        std::cout << std::fixed << std::setprecision(4) << weight << " ";
    }
    std::cout << "\nWeights (Percentage): ";
    for (const auto& weight : maxSharpePortfolio.weights) {
        std::cout << std::fixed << std::setprecision(2) << weight * 100 << "% ";
    }
    std::cout << "\nSharpe Ratio: " << std::fixed << std::setprecision(4) << maxSharpePortfolio.sharpeRatio << std::endl;

    // Output the weights for the minimized Volatility portfolio
    std::cout << "\nMinimized Volatility Portfolio:" << std::endl;
    std::cout << "Weights: ";
    for (const auto& weight : minVolatilityPortfolio.weights) {
        std::cout << std::fixed << std::setprecision(4) << weight << " ";
    }
    std::cout << "\nWeights (Percentage): ";
    for (const auto& weight : minVolatilityPortfolio.weights) {
        std::cout << std::fixed << std::setprecision(2) << weight * 100 << "% ";
    }
    std::cout << "\nVolatility: " << std::fixed << std::setprecision(4) << minVolatilityPortfolio.volatility << std::endl;
    return 0;
}
