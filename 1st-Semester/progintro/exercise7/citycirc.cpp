
//Given N cities, numbered from 1 to N (included) and arranged along a circular path
//(next to city k on the circular path is city k+1, when k < N, and city 1, when k = N) .
//A government official is to visit all the cities in the order mentioned above
//and settle the tax arrears of the citizens towards the state (tax payment)
//and the state towards the citizens (tax refund) in each city.
//For each city k (where 1 ≤ k ≤ N) an integer b_k is given that is equal to
//the sum of the tax outstandings of the residents of city k (this number can be positive, negative, or 0).
//So if b_k is positive, the employee leaves city k with b_k euros more than he had when he came,
//if b_k is negative, the employee leaves city k with |b_k| euros less,
//and if b_k is 0, the employee leaves city k with the same available amount.
//The employee cannot continue his tour if he appears to have a negative amount after visiting a city,
//as this indicates an inability to fulfill some tax refund obligations to the city.

//Write a program that finds the first city (that is, the one with the lowest number) from which,
//if the government employee starts his tour with zero euros, he will be able to complete it.

#include <iostream>  
  
using namespace std;  
  
const int MAX_N = 1000010;  
  
int num_cities, taxes[2 * MAX_N];  
  
int main () {  
    cin >> num_cities;  
    for (int i = 0; i < num_cities; i++)  
        cin >> taxes[i];  
  
    for (int i = num_cities; i < 2 * num_cities; i++)  
        taxes[i] = taxes[i - num_cities];  
  
    int start_city = 0;  
    while (start_city < num_cities) {  
        int sum = 0, idx;  
        bool is_valid = true;  
        for (idx = start_city; idx - start_city + 1 <= num_cities; idx++) {  
            sum += taxes[idx];  
            if (sum < 0) {  
                is_valid = false;
                break;  
            }
        } 
        if (is_valid) {  
            cout << start_city + 1 << endl;
            return 0;  
        } 
        else {
            start_city = idx + 1;
        }
    }  
    cout << "0" << endl;  
    return 0;  
}
