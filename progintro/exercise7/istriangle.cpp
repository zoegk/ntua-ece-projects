
//Write a program that reads three real numbers X, Y and Z and checks whether these numbers 
//can be the lengths of the sides of a triangle in the plane.

#include <iostream>

using namespace std;

int main() {
    double X, Y, Z;
    cin >> X >> Y >> Z;

    if (X + Y > Z && X + Z > Y && Y + Z > X) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
