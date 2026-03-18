#include <iostream>
#include <vector>
#include <iomanip>

struct Asset {
    const char* ticker;
    double price;
    double dividend_quarterly;
    int shares_owned;
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- 2026 DIVIDEND REINVESTMENT (DRIP) SIMULATOR ---\n";
    std::cout << "Target: Funding NVIDIA Exposure via JPM/IBM Yields\n\n";

    // Current March 18, 2026 Market Levels
    std::vector<Asset> income_assets = {
        {"IBM", 242.50, 1.68, 100}, // Example: 100 shares
        {"JPM", 329.00, 1.50, 80}   // Example: 80 shares
    };

    double nvda_price = 145.80; // Post-GTC 2026 price
    double total_quarterly_dividends = 0;

    for (const auto& a : income_assets) {
        double payout = a.dividend_quarterly * a.shares_owned;
        total_quarterly_dividends += payout;
        std::cout << "SOURCE: " << a.ticker << " | PAYOUT: $" << payout << "\n";
    }

    double new_nvda_shares = total_quarterly_dividends / nvda_price;

    std::cout << "---------------------------------------------------\n";
    std::cout << "TOTAL QUARTERLY INCOME: $" << total_quarterly_dividends << "\n";
    std::cout << "NEW NVDA SHARES ACQUIRED (FREE-ROLL): " << new_nvda_shares << "\n";
    std::cout << "ANNUALIZED NVDA ACQUISITION: " << new_nvda_shares * 4 << " shares\n";

    return 0;
}
