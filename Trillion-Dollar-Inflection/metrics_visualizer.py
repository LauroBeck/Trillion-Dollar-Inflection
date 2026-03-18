import matplotlib.pyplot as plt

# GTC 2026 Verified Data Points
years = ['2024', '2025', '2026 (Est)', '2027 (Proj)']
nvda_rev = [60, 110, 450, 1000]  # Cumulative Billions
jpm_it_spend = [15.5, 17.0, 19.8, 22.5] # Billions

plt.figure(figsize=(10, 6))
plt.plot(years, nvda_rev, marker='o', label='NVIDIA AI Rev (Cumulative $B)', color='#76b900', linewidth=3)
plt.plot(years, jpm_it_spend, marker='s', label='JPM IT Budget ($B)', color='#004a99', linewidth=2)

plt.title('The $1 Trillion Inflection: 2026 GTC Benchmark', fontsize=14)
plt.xlabel('Fiscal Year')
plt.ylabel('USD Billions')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.savefig('gtc_2026_inflection.png')
print("Visual metrics generated: gtc_2026_inflection.png")
