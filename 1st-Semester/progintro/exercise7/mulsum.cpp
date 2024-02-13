
//Given a sequence of N natural numbers and a positive natural number M. 
//The maximum multiple of M that can be obtained as the sum of (any) 
//consecutive terms of the sequence is required.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> maxim(M, 0), minim(M, 0);
    int s = 0;

    for (int i = 0; i < N; i++) {
        int u;
        cin >> u;
        s += u;
        maxim[s % M] = s;
        if (!minim[s % M] && s % M > 0) {
            minim[s % M] = s;
        }
    }

    int ans = 0;
    for (int i = 0; i < M; i++) {
        ans = max(ans, maxim[i] - minim[i]);
    }

    cout << ans << endl;

    return 0;
}
