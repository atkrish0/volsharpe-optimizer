#ifndef PORTFOLIOSTRATEGY_H
#define PORTFOLIOSTRATEGY_H

#include <vector>
#include "PortfolioOptimizer.h"

class PortfolioStrategy {
public:
    PortfolioStrategy() = default;
    virtual ~PortfolioStrategy() = default;

    // Method to execute the strategy
    virtual PortfolioResult executeStrategy(const std::vector<PortfolioResult>& portfolios) = 0;
};

#endif
