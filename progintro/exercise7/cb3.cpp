
//Some natural numbers, such as 17, can be written as the sum of three cubes of natural numbers: 
//17 = 1^3 + 2^3 + 2^3. Others, such as 42, cannot be written in this form. 
//Some natural numbers, such as 251, can be written in this form in 
//more than one way: 251 = 1^3 + 5^3 + 5^3 = 2^3 + 3^3 + 6^3.

#include <iostream>

using namespace std;

int main()
{
    int n, T;
    int *cubes = new int[1001];
    for (int i = 0; i <= 1000; i++)
    {
        cubes[i] = i * i * i;
    }

    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> n;
        int counter = 0;
        int a, b, c;
        for (a = 0; a <= 1000; a++)
        {
            if (cubes[a] > n)
                break;
            c = 1000;
            for (b = a; b <= 1000; b++)
            {
                if (cubes[a] + cubes[b] > n)
                    break;
                while (cubes[a] + cubes[b] + cubes[c] > n)
                {
                    c--;
                }
                if (c < b)
                    break;
                if (cubes[a] + cubes[b] + cubes[c] == n)
                    counter++;
            }
        }

        cout << counter << endl;
    }

    return 0;
}
