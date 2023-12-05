#include "MinVolatilityPortfolio.h"
#include <limits>

PortfolioResult MinVolatilityPortfolio::executeStrategy(const std::vector<PortfolioResult>& portfolios) {
    double minVolatility = std::numeric_limits<double>::max();
    PortfolioResult minVolatilityPortfolio;

    for (const auto& portfolio : portfolios) {
        if (portfolio.volatility < minVolatility) {
            minVolatility = portfolio.volatility;
            minVolatilityPortfolio = portfolio;
        }
    }

    return minVolatilityPortfolio;
}
