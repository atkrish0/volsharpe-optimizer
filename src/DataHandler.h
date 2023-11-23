#include <Eigen/Dense>
#include <string>
#include <vector>

class DataHandler {
public:
    static Eigen::MatrixXd readCSV(const std::string& file, int rows, int cols);

private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
};
