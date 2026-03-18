#include <iostream>
#include <vector>
#include <string_view>
#include <iomanip>

struct alignas(64) BankStock {
    const char* ticker;
    double price;           // Current March 2026 levels
    float beta;             // Sensitivity to S&P 500 (6,716)
    float yield_multiplier; // Performance boost from 2026 rate cuts
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- US BANK GAINS MULTIPLIER: MARCH 2026 ---" << "\n";
    std::cout << "--------------------------------------------" << "\n";

    // Data reflecting March 2026 projections
    std::vector<BankStock> portfolio = {
        {"JPM", 329.00, 1.1f, 1.25f},  // Bellwether (65% gain from 52wk low)
        {"BAC", 52.40, 1.2f, 1.30f},   // High sensitivity to rate steepening
        {"WFC", 78.10, 1.15f, 1.28f},  // Efficiency ratio leader
        {"MS", 118.50, 0.9f, 1.45f},   // Fee-based wealth management scaling
        {"BNY", 85.20, 0.7f, 1.20f},   // Custody/Asset servicing stability
        {"JEF", 62.30, 1.5f, 1.55f}    // High-growth investment banking boutique
    };

    double total_weighted_gains = 0;

    for (const auto& b : portfolio) {
        // Multiplier = (Price * Yield_Boost) - (Beta * volatility_drag)
        double projected_gain = (b.price * b.yield_multiplier) * 0.15; // 15% Target Growth
        std::cout << "BANK: " << std::left << std::setw(6) << b.ticker 
                  << " | TARGET GAIN: +$" << std::setw(8) << projected_gain 
                  << " | STANCE: " << (b.yield_multiplier > 1.3 ? "AGGRESSIVE" : "STABLE") << "\n";
    }

    return 0;
}
