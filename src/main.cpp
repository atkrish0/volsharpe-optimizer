#include <iostream>
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
    Eigen::MatrixXd corrMatrix = Statistics::correlationMatrix(returns);

    // Output stats
    std::cout << "Mean Daily Returns:\n" << meanReturns << "\n\n";
    std::cout << "Covariance Matrix:\n" << covMatrix << "\n\n";
    std::cout << "Volatility:\n" << volatility << "\n\n";
    std::cout << "Correlation Matrix:\n" << corrMatrix << "\n\n";

    // Set the number of random portfolio weights to generate
    int numPortfolios = 50000;
    std::vector<PortfolioResult> optimizedPortfolios = PortfolioOptimizer::optimizePortfolio(
        meanReturns, covMatrix, numPortfolios, numberOfColumns);

    // Strategy Execution
    MaxSharpePortfolio maxSharpeStrategy;
    MinVolatilityPortfolio minVolStrategy;

    PortfolioResult maxSharpePortfolio = maxSharpeStrategy.executeStrategy(optimizedPortfolios);
    PortfolioResult minVolatilityPortfolio = minVolStrategy.executeStrategy(optimizedPortfolios);

    // Output the weights for the max Sharpe ratio portfolio
    cout << "Max Sharpe Ratio Portfolio Weights:" << endl;
    for (double weight : maxSharpePortfolio.weights) {
        cout << weight << " ";
    }
    cout << "\nSharpe Ratio: " << maxSharpePortfolio.sharpeRatio << endl;

    // Output the weights for the min Volatility portfolio
    cout << "Min Volatility Portfolio Weights:" << endl;
    for (double weight : minVolatilityPortfolio.weights) {
        cout << weight << " ";
    }
    cout << "\nVolatility: " << minVolatilityPortfolio.volatility << endl;

    // Initialize variables to store the max Sharpe and min Volatility portfolios
    PortfolioResult maxSharpePortfolio;
    PortfolioResult minVolatilityPortfolio;
    // Initializing variables to the opposite ends of their appropriate spectrum 
    // i.e. max for volatilityy and min for sharpe ratio.
    // through the optimization process thiss value will change to the correct values
    double maxSharpe = std::numeric_limits<double>::lowest();
    double minVolatility = std::numeric_limits<double>::max();

    // Iterate through the portfolios to find the desired ones
    // i.e the ones with max sharpe ratio and min volatility
    for (const auto& portfolio : optimizedPortfolios) {
        if (portfolio.sharpeRatio > maxSharpe) {
            maxSharpe = portfolio.sharpeRatio;
            maxSharpePortfolio = portfolio;
        }
        if (portfolio.volatility < minVolatility) {
            minVolatility = portfolio.volatility;
            minVolatilityPortfolio = portfolio;
        }
    }

    // Output the weights for the max Sharpe ratio portfolio
    std::cout << "Max Sharpe Ratio Portfolio Weights:" << std::endl;
    for (double weight : maxSharpePortfolio.weights) {
        std::cout << weight << " ";
    }
    std::cout << "\nSharpe Ratio: " << maxSharpePortfolio.sharpeRatio << std::endl;

    // Output the weights for the min Volatility portfolio
    std::cout << "Min Volatility Portfolio Weights:" << std::endl;
    for (double weight : minVolatilityPortfolio.weights) {
        std::cout << weight << " ";
    }
    std::cout << "\nVolatility: " << minVolatilityPortfolio.volatility << std::endl;

    return 0;
}
