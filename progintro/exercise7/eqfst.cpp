
//Write a program that calculates the solution of the quadratic equation a*x+b=0.

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double a, b;
    cin >> a >> b;

    if (a != 0) {
        if (b == 0) cout << fixed << setprecision(6) << 0.0 << endl;
        else cout << fixed << setprecision(6) << (-b / a) << endl;
    }
    else if (a == 0 && b == 0) cout << "trivial" << endl;
    else cout << "impossible" << endl;

    return 0;
}
