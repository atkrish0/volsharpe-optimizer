#include "DataHandler.h"
#include <fstream>
#include <sstream>

// Read CSV file and return data in Eigen::MatrixXd format
Eigen::MatrixXd DataHandler::readCSV(const std::string& file, int rows, int cols) {

    std::ifstream inFile(file);
    std::string line;
    Eigen::MatrixXd data(rows, cols);
    int row = 0;
    
    while (std::getline(inFile, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < cols) {
            // Error handling for insufficient columns
            continue;
        }
        for (int col = 0; col < cols; col++) {
            try {
                data(row, col) = std::stod(tokens[col]);
            } catch (const std::invalid_argument& e) {
                // Error handling for invalid string-to-double conversion
                // e.g., set a default value or log an error message
            }
        }
        row++;
    }
    return data;
}

// Helper function to split a string using a delimiter
std::vector<std::string> DataHandler::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}