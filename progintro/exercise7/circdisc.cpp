
//Write a program that reads two real numbers X and Y and returns the location of the 
//point with coordinates (X, Y) relative to the unit circular disk.

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x, y;
    cin >> x >> y;

    double distance = sqrt(x * x + y * y);

    if (distance < 1.0) {
        cout << "inside" << endl;
    } else if (distance > 1.0) {
        cout << "outside" << endl;
    } else {
        cout << "border" << endl;
    }

    return 0;
}
