
//The world football championship (mundial) was held for the first time in 1930. 
//Since then, it has been organized every 4 years. 
//But in 1942 and 1946 it was not done, because of the war.

//Write a program that reads a year and checks if it is a World Cup year or not.

#include <iostream>

using namespace std;

int main() {
    int year;
    cin >> year;

    if ((year >= 1930) && ((year - 1930) % 4 == 0) && (year != 1942) && (year !=1946)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
