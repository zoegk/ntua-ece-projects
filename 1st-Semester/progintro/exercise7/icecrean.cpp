
//N children live along a straight road. Each child i resides at a different integer coordinate a_i on the street. 
//Summer is approaching, and the neighborhood ice cream shop is thinking about where on the street to set up its kiosk. 
//The ice cream shop knows that each child is willing to travel a distance less than or equal to K to buy ice cream. 
//So he wants to set up his kiosk where he can serve as many children as possible.

//Write a program that calculates the maximum number of children the ice cream parlor can serve.

//Note: The distance between two points with x and y coordinates on the road is equal to |x - y|.

#include <iostream>

using namespace std;

int main() {
    int numChildren, distance, maxChildren = 0, start = 0, end = 1, diff;
    cin >> numChildren >> distance;

    int coordinates[numChildren];

    for (int i = 0; i < numChildren; i++) {
        cin >> coordinates[i];
    }

    while (end < numChildren) {
        diff = coordinates[end] - coordinates[start];
        if (diff <= 2 * distance) {
            end++;
            if (end - start > maxChildren) {
                maxChildren = end - start;
            }
        } else {
            start++;
        }
    }
    cout << maxChildren << endl;

    return 0;
}
