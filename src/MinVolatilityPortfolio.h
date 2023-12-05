#ifndef MINVOLATILITYPORTFOLIO_H
#define MINVOLATILITYPORTFOLIO_H

#include "PortfolioStrategy.h"

class MinVolatilityPortfolio : public PortfolioStrategy {
public:
    // Implementation specific to Min volatility strategy
    PortfolioResult executeStrategy(const std::vector<PortfolioResult>& portfolios) override;
};

#endif