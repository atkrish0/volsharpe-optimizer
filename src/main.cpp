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

    return 0;
}
