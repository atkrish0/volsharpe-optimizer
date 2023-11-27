#include <iostream>
#include "DataHandler.h"
#include "Statistics.h"
#include "PortfolioOptimizer.h"

using namespace std;

int main() {

    // Read stock prices from CSV
    std::string filePath = "data/portfolio.csv";
    int numberOfRows = 494; 
    int numberOfColumns = 5; 
    Eigen::MatrixXd portfolio = DataHandler::readCSV(filePath);

    // Calculate daily returns, mean returns, etc. as before
    Eigen::MatrixXd returns = Statistics::calculateReturns(portfolio);
    Eigen::VectorXd meanReturns = Statistics::meanDailyReturns(returns);
    Eigen::MatrixXd covMatrix = Statistics::covarianceMatrix(returns);
    Eigen::VectorXd volatility = Statistics::volatility(returns);
    Eigen::MatrixXd corrMatrix = Statistics::correlationMatrix(returns);

    // Output stats
    std::cout << "Mean Daily Returns:\n" << meanReturns << "\n\n";
    std::cout << "Covariance Matrix:\n" << covMatrix << "\n\n";
    std::cout << "Volatility:\n" << volatility << "\n\n";
    std::cout << "Correlation Matrix:\n" << corrMatrix << "\n\n";

    // Set the number of random portfolio weights to generate
    int numPortfolios = 50000;

    // Call the PortfolioOptimizer to optimize portfolios
    std::vector<PortfolioResult> optimizedPortfolios = PortfolioOptimizer::optimizePortfolio(
        meanReturns, covMatrix, numPortfolios, numberOfColumns);

    // Example: Print the results of the first optimized portfolio
    if (!optimizedPortfolios.empty()) {
        const PortfolioResult& firstPortfolio = optimizedPortfolios.front();
        std::cout << "First Optimized Portfolio:" << std::endl;
        std::cout << "Return: " << firstPortfolio.return_ << std::endl;
        std::cout << "Volatility: " << firstPortfolio.volatility << std::endl;
        std::cout << "Sharpe Ratio: " << firstPortfolio.sharpeRatio << std::endl;
        std::cout << "Weights: ";
        for (double weight : firstPortfolio.weights) {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
