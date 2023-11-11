#include <iostream>
#include "MarketData.hpp"
#include "Statistics.h"

using namespace std;

int main() {
    std::string filename = "market_data.csv"; // Your local CSV file with closing prices
    MarketData marketData(filename);

    Eigen::MatrixXd covMatrix = marketData.getCovarianceMatrix();
    std::cout << "Covariance Matrix:\n" << covMatrix << std::endl;
    
    // Assuming 'portfolio' is an Eigen::MatrixXd containing the stock prices
    Eigen::MatrixXd portfolio; // Populate this with your data

    // Calculate daily returns
    Eigen::MatrixXd returns = Statistics::calculateReturns(portfolio);

    // Mean daily returns
    Eigen::VectorXd meanReturns = Statistics::meanDailyReturns(returns);

    // Covariance matrix
    Eigen::MatrixXd covMatrix = Statistics::covarianceMatrix(returns);

    // Volatility
    Eigen::VectorXd volatility = Statistics::volatility(returns);

    // Correlation matrix
    Eigen::MatrixXd corrMatrix = Statistics::correlationMatrix(returns);

    // Example of output (you might format it as needed)
    std::cout << "Mean Daily Returns:\n" << meanReturns << "\n\n";
    std::cout << "Covariance Matrix:\n" << covMatrix << "\n\n";
    std::cout << "Volatility:\n" << volatility << "\n\n";
    std::cout << "Correlation Matrix:\n" << corrMatrix << "\n\n";

    return 0;
}
