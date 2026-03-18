#include <iostream>
#include <vector>
#include <string_view>
#include <iomanip>
#include <chrono>

enum class Region : uint8_t { US, EU, ASIA };

struct alignas(64) MarketProjection {
    char client[16];
    double current_sales;      // In Billions
    double expansion_target;   // Target for 2027 ($1T Vision)
    Region region;
    float growth_multiplier;   // 5x Velocity factor
};

void track_projections(const std::vector<MarketProjection>& markets) {
    std::cout << std::left << std::setw(12) << "CLIENT" 
              << std::setw(8) << "REGION" 
              << std::setw(15) << "CURR ($B)" 
              << std::setw(15) << "TARGET ($B)" 
              << "VELOCITY\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& m : markets) {
        const char* reg_name = (m.region == Region::US) ? "US" : 
                               (m.region == Region::EU) ? "EU" : "ASIA";
        
        double projected = m.current_sales * m.growth_multiplier;
        
        std::cout << std::left << std::setw(12) << m.client 
                  << std::setw(8) << reg_name 
                  << std::setw(15) << m.current_sales 
                  << std::setw(15) << projected 
                  << (projected >= m.expansion_target ? "OVER-TARGET" : "EXPANDING") << "\n";
    }
}

int main() {
    std::cout << "--- JPM/IBM GLOBAL EXPANSION TRACKER (2026-2027) ---\n";
    
    // Projections based on the $1T Forecast and Bloomberg Data
    std::vector<MarketProjection> global_markets = {
        {"NVIDIA", 181.9, 1000.0, Region::US, 5.5f},   // Aggressive US AI Expansion
        {"Tencent", 310.9, 500.0, Region::ASIA, 1.8f}, // Asia Cloud Growth
        {"IBM", 60.5, 150.0, Region::EU, 2.5f},        // EU Hybrid Cloud Push
        {"SK Hynix", 140.5, 300.0, Region::ASIA, 2.2f} // Semi-conductor Expansion
    };

    track_projections(global_markets);
    return 0;
}
