#include "PortfolioDisplay.h"
#include <iomanip>

void PortfolioDisplay::displayPortfolio(const std::string& title, const PortfolioResult& portfolio) {
    using namespace std;

    cout << "\n" << title << ":" << endl;
    cout << "Weights: ";
    for (const auto& weight : portfolio.weights) {
        cout << fixed << setprecision(4) << weight << " ";
    }
    cout << "\nWeights (Percentage): ";
    for (const auto& weight : portfolio.weights) {
        cout << fixed << setprecision(2) << weight * 100 << "% ";
    }
    cout << "\nPortfolio Sharpe Ratio: " << fixed << setprecision(4) << portfolio.sharpeRatio << endl;
    cout << "Portfolio Volatility: " << fixed << setprecision(4) << portfolio.volatility << endl;
}
