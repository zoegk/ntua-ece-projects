#include <iostream>

using namespace std;

typedef double list[100]; 

int main() {
    int N, M;
    cin >> N >> M; 

    list rowSum, colSum;

    for (int i = 0; i < N; ++i) {
        double rowAvg = 0.0;
        for (int j = 0; j < M; ++j) {
            double num;
            cin >> num;
            rowAvg += num;
            if (i == 0) {
                colSum[j] = num;
            } else {
                colSum[j] += num;
            }
        }
        rowSum[i] = rowAvg / M; 
    }

    for (int j = 0; j < M; ++j) {
        colSum[j] /= N;
    }

    double avgRowAvg = 0.0;
    for (int i = 0; i < N; ++i) {
        avgRowAvg += rowSum[i];
    }
    avgRowAvg /= N;

    double avgColAvg = 0.0;
    for (int j = 0; j < M; ++j) {
        avgColAvg += colSum[j];
    }
    avgColAvg /= M;

    cout.precision(3);
    cout << fixed;
    
    cout << avgRowAvg << endl;

    cout << avgColAvg << endl;

    // Επεξήγηση: Η ισότητα των δύο αριθμών που υπολογίστηκαν παραπάνω δεν είναι τυχαία,
     // αλλά μάλλον αποτέλεσμα των ιδιοτήτων των μέσων όρων.
     // Και οι δύο υπολογισμοί περιλαμβάνουν την άθροιση όλων των στοιχείων του πίνακα και τη διαίρεση με τον συνολικό αριθμό των στοιχείων.
     // Επομένως, δίνουν το ίδιο αποτέλεσμα.
     
    return 0;
}

