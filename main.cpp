#include <iostream>
#include <cov_mat.h>
using namespace std;

int main() {
    std::string filename = "market_data.csv"; // Your local CSV file with closing prices
    MarketData marketData(filename);

    Eigen::MatrixXd covMatrix = marketData.getCovarianceMatrix();
    std::cout << "Covariance Matrix:\n" << covMatrix << std::endl;

    return 0;
}
