#include <iostream>
#include <vector>
#include <iomanip>

struct alignas(64) MarketCatalyst {
    const char* entity;
    double value;       // Billions
    const char* tech;   // Key 2026 Tech
    float multiplier;   // Growth velocity
};

int main() {
    std::cout << "--- TRILLION-DOLLAR INFLECTION: MARCH 18, 2026 ---" << "\n";
    std::cout << "GTC 2026 VERIFIED | TARGET: $1T SALES THRU 2027" << "\n\n";

    std::vector<MarketCatalyst> stats = {
        {"NVIDIA",   1000.0, "Vera Rubin / HBM4", 5.00f}, // Jensen's $1T Goal
        {"JPMORGAN", 19.8,   "Agentic Commerce",  1.10f}, // $19.8B Budget
        {"IBM",      15.7,   "Hybrid Cloud FCF",  1.25f}, // $15.7B FCF
        {"SK HYNIX", 140.5,  "HBM4 High-Volume",  2.20f}  // Rubin Supply Chain
    };

    std::cout << std::left << std::setw(12) << "ENTITY" 
              << std::setw(12) << "CAPEX/VAL" 
              << std::setw(20) << "CORE TECH" 
              << "STATUS\n" << std::string(60, '-') << "\n";

    for (const auto& s : stats) {
        const char* unit = (s.value >= 1000.0) ? "T" : "B";
        double display_val = (s.value >= 1000.0) ? s.value / 1000.0 : s.value;

        std::cout << std::left << std::setw(12) << s.entity 
                  << "$" << std::setw(6) << display_val << unit << "      "
                  << std::setw(20) << s.tech 
                  << (s.multiplier > 2.0 ? "HYPER-SCALE" : "STABLE") << "\n";
    }
    return 0;
}
