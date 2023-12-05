#ifndef MAXSHARPEPORTFOLIO_H
#define MAXSHARPEPORTFOLIO_H

#include "PortfolioStrategy.h"

class MaxSharpePortfolio : public PortfolioStrategy {
public:
    MaxSharpePortfolio() = default;

    // Implementation specific to Max Sharpe Ratio strategy
    PortfolioResult executeStrategy(const std::vector<PortfolioResult>& portfolios) override;
};

#endif
