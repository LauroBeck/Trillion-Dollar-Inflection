#include <iostream>
#include <vector>
#include <string_view>
#include <string>

// 1. Memory Alignment: Aligning to cache lines (64 bytes) prevents "false sharing"
struct alignas(64) MarketDataMessage {
    char symbol[8];     // Fixed-size char array is faster than std::string (no heap)
    double price;
    int quantity;
};

class ExecutionEngine {
public:
    // 2. Pre-fetching/Inlining: processMarketData is a candidate for 'inline'
    // 3. Removed Sleep: Real-time engines use 'busy-waiting' or lock-free queues
    inline void processMarketData(const MarketDataMessage& message) noexcept {
        executeTrade(message);
    }

private:
    // 4. Optimization: Use '\n' instead of std::endl to avoid unnecessary buffer flushes
    // 5. noexcept: Tells the compiler it can optimize without worrying about exceptions
    void executeTrade(const MarketDataMessage& message) noexcept {
        std::cout << "Executing: " << message.symbol 
                  << " @ " << message.price << '\n';
    }
};

int main() {
    // 6. Fast I/O: Synchronizing with C stdio slows down C++ streams significantly
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ExecutionEngine engine;
    
    // Initialize with fixed-width char array for zero-allocation
    MarketDataMessage msg = {"IBM", 252.58, 1000}; 

    // Simulation loop
    for(int i = 0; i < 5; ++i) {
        engine.processMarketData(msg);
    }

    return 0;
}
