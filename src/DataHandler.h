#include <Eigen/Dense>
#include <string>
#include <vector>

class DataHandler {
public:
    // Function to read CSV data into an Eigen matrix
    static Eigen::MatrixXd readCSV(const std::string& file);

private:
    // Helper function to split a string by a delimiter
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

