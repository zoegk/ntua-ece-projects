#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void simplifyFraction(int& num, int& denom) {
    int divisor = gcd(abs(num), abs(denom));
    num /= divisor;
    denom /= divisor;
    
}

int main() {
    int N;
    cin >> N; 

    for (int i = 0; i < N; ++i) {
        char op;
        int num1, denom1, num2, denom2;
        
        cin >> op >> num1 >> denom1 >> num2 >> denom2;

        if (denom1 == 0 || denom2 == 0) {
            cout << "error" << endl;
            continue;
        }

        int result_num, result_denom;
        switch (op) {
            case '+':
                result_num = num1 * denom2 + num2 * denom1;
                result_denom = denom1 * denom2;
                break;
            case '-':
                result_num = num1 * denom2 - num2 * denom1;
                result_denom = denom1 * denom2;
                break;
            case '*':
                result_num = num1 * num2;
                result_denom = denom1 * denom2;
                break;
            case '/':
                if (num2 == 0) {
                    cout << "error" << endl;
                    continue;
                }
                result_num = num1 * denom2;
                result_denom = denom1 * num2;
                break;
            default:
                cout << "error" << endl;
                continue;
        }

        simplifyFraction(result_num, result_denom);

        int whole_part = result_num / result_denom;
        int remainder = abs(result_num) % abs(result_denom);

        if (whole_part == 0 & result_num*result_denom < 0 ) {
            cout << "-0 " << abs(result_num) << " " << abs(result_denom) << endl;
        }
        else if (whole_part == 0 & result_num*result_denom > 0 ) {
            cout << "0 " << abs(result_num) << " " << abs(result_denom) << endl;
        }
        else {
            cout << whole_part << " " << abs(remainder) << " " << abs(result_denom) << endl;
        }
    }

    return 0;
}
