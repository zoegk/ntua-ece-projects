#include <iostream>
#include <string>
#include <array>
using namespace std;

int main() {
    
    int N, M, u, v, per =0;
    int pathpart[4];
    
    cin >> N >> M;
    int nodeval[N];
    for (int i=0; i<N; i++){
        nodeval[i]=0;
    }
    
    for(int i=0; i<M; i++){
        cin >> u >> v;
        nodeval[u]++;
        nodeval[v]++;
    }
    
    for(int j=0; j<N; j++){
        if(nodeval[j]%2!=0){
            pathpart[per]=j;
            per ++;
            if (per>2){
                cout << "IMPOSSIBLE" << endl;
                exit(0);
            }
        }
    }
    
    if (per==0){
        cout << "CYCLE" << endl;
    }
    
    else if (per == 2) {
        cout << "PATH ";
        if (pathpart[0] < pathpart[1]){
            cout << pathpart[0] << " " << pathpart[1] << endl;
        }
        else {
            cout << pathpart[1] << " " << pathpart[0] << endl;
        }
    }
    
    else{
        cout << "IMPOSSIBLE" <<endl;
    }
}

