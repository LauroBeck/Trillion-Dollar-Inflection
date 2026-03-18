#include <iostream>
#include <vector>
#include <cstdint>   // Fixed: Required for uint32_t
#include <cstring>   // Fixed: For strncpy safety
#include <sched.h> 
#include <unistd.h>

struct alignas(64) PriceUpdate {
    double price;
    uint32_t volume;
    char ticker[8];
};

void set_cpu_affinity(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

int main() {
    set_cpu_affinity(0);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const size_t BATCH = 1000000;
    std::vector<PriceUpdate> updates;
    updates.reserve(BATCH);

    for (size_t i = 0; i < BATCH; ++i) {
        PriceUpdate msg;
        msg.price = 150.0 + (i * 0.01);
        msg.volume = static_cast<uint32_t>(i);
        // Direct assignment for speed
        msg.ticker[0] = 'N'; msg.ticker[1] = 'V'; msg.ticker[2] = 'D'; msg.ticker[3] = 'A';
        msg.ticker[4] = '\0';
        
        updates.push_back(msg);
    }

    double checksum = 0;
    // Pointer-based access is often faster for large batches
    const PriceUpdate* data = updates.data();
    for (size_t i = 0; i < BATCH; ++i) {
        checksum += data[i].price;
    }

    std::cout << "Processed: " << BATCH << " | Checksum: " << checksum << "\n";
    return 0;
}
