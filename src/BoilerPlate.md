#set number of runs of random portfolio weights
num_portfolios = 50000

#these are the column heads of the portfolio.csv input file, whihc will have closing prices of these 5 stocks
stock = ['Axis', 'Cipla', 'Fortis', 'Jet', 'Titan']

#increased the size of the array to hold the weight values for each stock
results = np.zeros((4+len(stock)-1,num_portfolios))

for i in range(num_portfolios):
    #select random weights for portfolio holdings
    w = np.array(np.random.random(5))
    #rebalance weights to sum to 1, so that total portfolio alloc stays within 100%
    w /= np.sum(w)
    portfolio_return = np.sum(mean_daily_returns * w) * 252
    portfolio_vol = np.sqrt(np.dot(w.T,np.dot(cov_matrix, w))) * np.sqrt(252)
    results[0,i] = portfolio_return
    results[1,i] = portfolio_vol
    #portfolio_sharpe = portfolio_return / portfolio_vol 
    results[2,i] = results[0,i]/results[1,i]
    #iterate through the weight vector and add data to results array
    for j in range(len(w)):
        results[j+3,i] = w[j]

result_frame = pd.DataFrame(results.T,columns=['ret','stdev','sharpe',stock[0],stock[1],stock[2],stock[3],stock[4]])

#locate position of portfolio with highest Sharpe Ratio
max_sharpe_port = result_frame.iloc[result_frame['sharpe'].idxmax()]

#locate positon of portfolio with minimum standard deviation
min_vol_port = result_frame.iloc[result_frame['stdev'].idxmin()]


Need to use the quantlib or anyother c++ library to translate this to c++. the output of all this needs to the