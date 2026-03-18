#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <atomic>
#include <thread>
#include <sched.h>

// Cache-aligned packet for zero-latency transfer
struct alignas(64) TradePacket {
    double price;
    uint32_t volume;
    char origin[4]; // "JPM"
    char target[4]; // "IBM"
};

// High-resolution timer utility
struct Timer {
    std::chrono::high_resolution_clock::time_point start;
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    double elapsed_ms() {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};

void pin_thread(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

int main() {
    const size_t BATCH_SIZE = 5'000'000;
    std::vector<TradePacket> jpm_signals;
    jpm_signals.reserve(BATCH_SIZE);

    std::cout << "--- JPM -> IBM Simulation Init ---" << "\n";
    
    // 1. Generation Phase (JPMorgan Signal Generation)
    for (size_t i = 0; i < BATCH_SIZE; ++i) {
        TradePacket p;
        p.price = 190.0 + (i * 0.001);
        p.volume = 100 + (i % 1000);
        p.origin[0] = 'J'; p.origin[1] = 'P'; p.origin[2] = 'M'; p.origin[3] = '\0';
        p.target[0] = 'I'; p.target[1] = 'B'; p.target[2] = 'M'; p.target[3] = '\0';
        jpm_signals.push_back(p);
    }

    // 2. Execution Phase (IBM Processing Bridge)
    pin_thread(1); // Pin execution to a specific high-perf core
    
    Timer t;
    double total_notional = 0;
    const TradePacket* __restrict__ data = jpm_signals.data();

    #pragma GCC ivdep // Ignore vector dependencies
    for (size_t i = 0; i < BATCH_SIZE; ++i) {
        // Core execution logic: simulate a price-volume weighted sum
        total_notional += data[i].price * data[i].volume;
    }
    
    double duration = t.elapsed_ms();
    
    std::cout << "Batch Size: " << BATCH_SIZE << " messages" << "\n";
    std::cout << "Total Time: " << duration << " ms" << "\n";
    std::cout << "Throughput: " << (BATCH_SIZE / (duration / 1000.0)) / 1e6 << " Million msg/sec" << "\n";
    std::cout << "Avg Latency: " << (duration * 1e6) / BATCH_SIZE << " nanoseconds" << "\n";
    std::cout << "Notional Checksum: " << total_notional << "\n";

    return 0;
}
