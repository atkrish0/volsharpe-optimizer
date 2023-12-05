#ifndef MINVOLATILITYPORTFOLIO_H
#define MINVOLATILITYPORTFOLIO_H

#include "PortfolioStrategy.h"

class MinVolatilityPortfolio : public PortfolioStrategy {
public:
    PortfolioResult executeStrategy(const std::vector<PortfolioResult>& portfolios) override;
};

#endif // MINVOLATILITYPORTFOLIO_H
