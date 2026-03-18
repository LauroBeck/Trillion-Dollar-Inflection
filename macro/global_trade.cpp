#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

struct alignas(64) GlobalTransaction {
    uint64_t tx_id;
    double amount;
    const char* route; // e.g., "NYC -> LDN -> TYO"
    long long latencies[3]; // Latency hops in microseconds
};

void simulate_hop(const char* region, int delay_ms) {
    // In a real system, this is where the fiber-optic speed of light hits.
    // NYC to LDN is ~60ms. LDN to TYO is ~150ms.
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- Global Transaction Bridge: ASIA | EU | US ---" << "\n";
    
    const int num_trades = 5;
    for (int i = 1; i <= num_trades; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        
        // Step 1: US Initiation (JPM - New York)
        simulate_hop("US", 5); 
        auto p1 = std::chrono::high_resolution_clock::now();
        
        // Step 2: EU Validation (London/Frankfurt)
        simulate_hop("EU", 60); 
        auto p2 = std::chrono::high_resolution_clock::now();
        
        // Step 3: ASIA Clearing (IBM - Tokyo)
        simulate_hop("ASIA", 150); 
        auto p3 = std::chrono::high_resolution_clock::now();

        auto total = std::chrono::duration_cast<std::chrono::milliseconds>(p3 - start).count();
        
        std::cout << "[TX ID: " << 1000 + i << "] Route: US -> EU -> ASIA | Total Time: " 
                  << total << "ms" << "\n";
    }

    return 0;
}
