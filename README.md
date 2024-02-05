# volsharpe-optimizer

## GEN:
tldr: Rudimentary optimer which provides portfolio weights for maximum sharpe/minimized volatility portfolio
Implements a portfolio optimization framework in C++, with results compared to equal weighted out-of-sample data.

## Data:

A sanitized dataset consisting of closing price of a equity securities listed in the Bombay Stock Exchange.

## Procedure:

#1: Understand the external libraries that will be used and for what purposes:
* C++ compiler with C++11 support or higher
* QuantLib library
* Eigen library (for matrix operations)
* NLopt library (for numerical optimization)
* Gnuplot and the Gnuplot C++ interface (for plotting)

#2: Getting the data:
Will use preexisting data set of list companies in the Bombay Stock Exchange.

#3: Calculate historical prices and covariance matrices - using Eigen library in C++


