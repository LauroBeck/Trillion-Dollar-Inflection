#include <iostream>
#include <vector>
#include <string_view>
#include <iomanip>

struct alignas(64) FinancialEntity {
    const char* name;
    double value;       // In Billions (USD)
    const char* scale;  // "Million" or "Billion"
    float multiplier;   // Growth factor for 2026-2027
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- JPMORGAN TECH SPEND -> IBM/NVIDIA REVENUE BRIDGE ---\n";
    std::cout << "MARCH 2026 | CAPITAL FLOW HIERARCHY\n";
    std::cout << "-------------------------------------------------------\n";

    // Data reflecting the $17B JPM spend and $1T NVIDIA Forecast
    std::vector<FinancialEntity> entities = {
        {"JPM TECH BUDGET", 17.50, "Billion", 1.15f}, // The Source
        {"IBM PaaS REV",     8.20,  "Billion", 1.25f}, // The Infrastructure
        {"NVDA AI SALES",   181.90, "Billion", 5.50f}, // The Hardware ($1T Target)
        {"SK HYNIX HBM",    140.50, "Billion", 2.20f}, // The Supply Chain
        {"TX PROCESSING",   950.00, "Million", 3.10f}  // The Daily Batch Flow
    };

    for (const auto& e : entities) {
        double future_val = e.value * e.multiplier;
        const char* final_scale = (future_val >= 1000.0) ? "Trillion" : e.scale;
        double display_val = (future_val >= 1000.0) ? future_val / 1000.0 : future_val;

        std::cout << "ENTITY: " << std::left << std::setw(15) << e.name 
                  << " | 2026: $" << std::setw(6) << e.value << " " << e.scale
                  << " | 2027 PROJ: $" << std::setw(6) << display_val << " " << final_scale 
                  << " | GAIN: " << (e.multiplier - 1.0f) * 100 << "%\n";
    }

    return 0;
}
