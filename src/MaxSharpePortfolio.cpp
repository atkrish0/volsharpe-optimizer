#include "MaxSharpePortfolio.h"
#include <limits>

PortfolioResult MaxSharpePortfolio::executeStrategy(const std::vector<PortfolioResult>& portfolios) {
    double maxSharpe = std::numeric_limits<double>::lowest();
    PortfolioResult maxSharpePortfolio;

    for (const auto& portfolio : portfolios) {
        if (portfolio.sharpeRatio > maxSharpe) {
            maxSharpe = portfolio.sharpeRatio;
            maxSharpePortfolio = portfolio;
        }
    }
    return maxSharpePortfolio;
}
