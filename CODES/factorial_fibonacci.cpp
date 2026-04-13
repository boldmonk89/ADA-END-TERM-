#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
 
// ── Factorial ───────────────────────────────────────────
long long factIterative(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
 
long long factRecursive(int n) {
    if (n <= 1) return 1;
    return n * factRecursive(n - 1);
}
 
// ── Fibonacci ───────────────────────────────────────────
long long fibIterative(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
    return b;
}
 
long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n-1) + fibRecursive(n-2);
}
 
int main() {
    int n = 10;
    cout << "=== FACTORIAL ==="  << endl;
    cout << "Iterative  : " << factIterative(n) << endl;
    cout << "Recursive  : " << factRecursive(n) << endl;
 
    cout << endl << "=== FIBONACCI (n=" << n << ") ==="  << endl;
    cout << "Iterative  : " << fibIterative(n)  << endl;
    cout << "Recursive  : " << fibRecursive(n)  << endl;
    return 0;
}
