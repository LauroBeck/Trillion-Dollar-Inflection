#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

struct alignas(64) FXRate {
    char pair[8];     // "KRW/USD"
    double rate;
};

struct CorporateTx {
    const char* client;
    double amount;    // In local currency (Millions)
    const char* cur;  // KRW, CNY, USD
};

class TreasuryConsolidator {
public:
    // Millions of USD
    double convert_to_usd(const CorporateTx& tx) const noexcept {
        if (tx.cur[0] == 'U') return tx.amount; // Already USD
        if (tx.cur[0] == 'K') return tx.amount * 0.00075; // KRW -> USD
        if (tx.cur[0] == 'C') return tx.amount * 0.14;    // CNY -> USD
        return 0.0;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(4);
    TreasuryConsolidator engine;

    std::vector<CorporateTx> incoming = {
        {"NVIDIA", 450.5, "USD"},
        {"SK Hynix", 820200.0, "KRW"}, // ~615M USD
        {"Tencent", 2200.0, "CNY"}     // ~308M USD
    };

    double total_vault_usd = 0;
    std::cout << "--- JPMORGAN GLOBAL CONSOLIDATION (USD) ---\n";

    for (const auto& tx : incoming) {
        double usd_val = engine.convert_to_usd(tx);
        total_vault_usd += usd_val;
        std::cout << "[REBALANCED] " << tx.client << " -> $" << usd_val << "M USD\n";
    }

    std::cout << "-------------------------------------------\n";
    std::cout << "TOTAL LIQUIDITY POOL: $" << total_vault_usd << "M USD\n";

    return 0;
}
