#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Eigen/Dense>

class MarketData {
private:
    Eigen::MatrixXd prices;
    Eigen::MatrixXd returns;

public:
    // Constructor
    MarketData(const std::string &filename) {
        loadData(filename);
        computeReturns();
    }

    void loadData(const std::string &filename) {
        std::ifstream file(filename);
        std::string line;
        std::vector<std::vector<double>> data;

        // Read data from CSV file
        while (getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<double> parsedRow;
            while (getline(lineStream, cell, ',')) {
                parsedRow.push_back(std::stod(cell));
            }
            data.push_back(parsedRow);
        }

        // Convert vector to Eigen::MatrixXd
        if (!data.empty()) {
            prices.resize(data.size(), data.front().size());
            for (size_t i = 0; i < data.size(); ++i) {
                for (size_t j = 0; j < data[i].size(); ++j) {
                    prices(i, j) = data[i][j];
                }
            }
        }
    }

    void computeReturns() {
        // Assuming daily prices, compute log returns
        returns.resize(prices.rows() - 1, prices.cols());
        for (int i = 1; i < prices.rows(); ++i) {
            returns.row(i - 1) = (prices.row(i).array() / prices.row(i - 1).array()).log();
        }
    }

    Eigen::MatrixXd getCovarianceMatrix() const {
        // Calculate covariance matrix of the returns
        Eigen::MatrixXd centered = returns.rowwise() - returns.colwise().mean();
        Eigen::MatrixXd cov = (centered.adjoint() * centered) / double(returns.rows() - 1);
        return cov;
    }
};
