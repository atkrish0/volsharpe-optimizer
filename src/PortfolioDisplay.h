#ifndef PORTFOLIODISPLAY_H
#define PORTFOLIODISPLAY_H

#include <iostream>
#include <vector>
#include "PortfolioOptimizer.h"

class PortfolioDisplay {
public:
    static void displayPortfolio(const std::string& title, const PortfolioResult& portfolio);
};

#endif
