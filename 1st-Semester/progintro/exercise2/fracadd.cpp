#include <iostream>
using namespace std;

int main() {
    int num1, denom1, num2, denom2;
    
    cin >> num1 >> denom1;
    
    cin >> num2 >> denom2;
    
    int sum_num = num1 * denom2 + num2 * denom1;
    int sum_denom = denom1 * denom2;
    
    cout << sum_num << " " << sum_denom << endl;
    
    return 0;
}
