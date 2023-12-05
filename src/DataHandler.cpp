#include "DataHandler.h"
#include <fstream>
#include <sstream>

// Read CSV file and return data in Eigen::MatrixXd format
Eigen::MatrixXd DataHandler::readCSV(const std::string& file) {
    std::ifstream inFile(file);
    std::string line;

    // Skipping the header line which has stock names
    std::getline(inFile, line);

    // Initialize the matrix for 494 rows and 5 columns (hardcoded based on our data)
    Eigen::MatrixXd data(494, 5); 
    int row = 0;
    
    while (std::getline(inFile, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() != 5) {
            // Handle error for rows with incorrect number of columns
            continue;
        }
        for (int col = 0; col < 5; col++) {
            try {
                data(row, col) = std::stod(tokens[col]);
            } // Handle error for invalid string-to-double conversion
            catch (const std::invalid_argument& e) {       
            }
        }
        row++;
        // Ensure we don't exceed the expected number of rows
        if (row >= 494) break; 
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