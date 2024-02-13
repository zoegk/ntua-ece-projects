
//Little Lucas is playing with his skate. But he gets tired easily, so he relies solely on the slope of the road. 
//Suppose that the road where Luke skates is divided into N small sections and that the slope of each of them is 
//represented by an integer. For example, if the number corresponding to a segment is 3, 
//then that segment is downhill and the speed of the skate will increase by 3 when passing through it. 
//Conversely, if the number is -4, then that section is uphill and the speed of the skate will decrease by 4 when passing through it. 
//Flat sections are represented by zero.

//Lucas can choose from which point on the road he will start with his skate. 
//His initial speed is zero and he wants to reach the end of the road at the maximum possible speed.

//Write a program that will find the maximum possible speed at the end of the road.

#include <iostream>

using namespace std;

int main() {
    int num_segments;
    cin >> num_segments;

    int current_speed = 0, max_speed = 0;
    int segments[num_segments];

    for (int i = 0; i < num_segments; ++i) {
        cin >> segments[i];
    }

    for (int j = num_segments - 1; j >= 0; --j) {
        current_speed += segments[j];
        if (current_speed > max_speed) {
            max_speed = current_speed;
        }
    }

    cout << max_speed << endl;

    return 0;
}
