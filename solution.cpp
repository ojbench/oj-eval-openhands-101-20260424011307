#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    long long min_val = min({a, b, c});
    long long min_seconds = LLONG_MAX;
    
    // Try each possible target value x where h == m == s == x
    for (long long x = 0; x < min_val; x++) {
        // We need to find minimum s > 0 such that:
        // (d + s) % a == x  (seconds position)
        // (e + (d + s) / a) % b == x  (minutes position)
        // (f + (e + (d + s) / a) / b) % c == x  (hours position)
        
        // First condition: (d + s) % a == x
        // s ≡ (x - d) (mod a)
        // Minimum positive s: s = ((x - d) % a + a) % a
        // But if this is 0, we need s = a (next cycle)
        
        long long s_base = ((x - d) % a + a) % a;
        if (s_base == 0) s_base = a;
        
        // Try different cycles
        for (long long cycle = 0; cycle < a * b; cycle++) {
            long long s = s_base + cycle * a;
            if (s <= 0) continue;
            if (s >= min_seconds) break;
            
            // Check minute condition
            long long total_mins = e + (d + s) / a;
            if (total_mins % b != x) continue;
            
            // Check hour condition
            long long total_hours = f + total_mins / b;
            if (total_hours % c != x) continue;
            
            // Found a valid solution
            min_seconds = s;
            break;
        }
    }
    
    cout << min_seconds << endl;
    
    return 0;
}
