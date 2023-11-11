#include <Eigen/Dense>
#include <vector>

class Statistics {
public:
    static Eigen::MatrixXd calculateReturns(const Eigen::MatrixXd& prices);
    static Eigen::VectorXd meanDailyReturns(const Eigen::MatrixXd& returns);
    static Eigen::MatrixXd covarianceMatrix(const Eigen::MatrixXd& returns);
    static Eigen::VectorXd volatility(const Eigen::MatrixXd& returns);
    static Eigen::MatrixXd correlationMatrix(const Eigen::MatrixXd& returns);
};
