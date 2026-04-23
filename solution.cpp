#include <iostream>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    long long h = f, m = e, s = d;
    long long seconds = 0;
    
    // We need to find the next time when h == m == s
    // Start by advancing at least 1 second
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
    
    cout << seconds << endl;
    
    return 0;
}
