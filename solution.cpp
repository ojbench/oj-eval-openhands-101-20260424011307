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
        // We need t > 0 such that:
        // (d + t) mod a = x
        // (e + (d + t) / a) mod b = x
        // (f + (e + (d + t) / a) / b) mod c = x
        
        // From the first condition: t = (x - d) + k * a
        // From the second: k = (x - e) + j * b  
        // From the third: j = (x - f) + m * c
        
        // Try different values of m
        for (long long m = 0; m <= 1; m++) {
            long long j = ((x - f) % c + c) % c + m * c;
            long long k = ((x - e) % b + b) % b + j * b;
            long long t = ((x - d) % a + a) % a + k * a;
            
            // Ensure t > 0
            if (t == 0) {
                // Need to go to the next cycle
                // This means we need the next occurrence of x
                // We can add a full day cycle
                continue;
            }
            
            // Verify the solution
            long long new_s = (d + t) % a;
            long long mins_total = e + (d + t) / a;
            long long new_m = mins_total % b;
            long long hours_total = f + mins_total / b;
            long long new_h = hours_total % c;
            
            if (new_s == x && new_m == x && new_h == x) {
                if (t < min_seconds) {
                    min_seconds = t;
                }
                break;
            }
        }
    }
    
    // Handle the case where current time is already at h==m==s
    // In this case, we need to find the next occurrence
    if (min_seconds == LLONG_MAX) {
        // Fallback to simulation for edge cases
        long long h = f, m = e, s = d;
        long long seconds = 0;
        
        do {
            seconds++;
            s++;
            
            if (s == a) {
                s = 0;
                m++;
                if (m == b) {
                    m = 0;
                    h++;
                    if (h == c) {
                        h = 0;
                    }
                }
            }
        } while (h != m || m != s);
        
        min_seconds = seconds;
    }
    
    cout << min_seconds << endl;
    
    return 0;
}
