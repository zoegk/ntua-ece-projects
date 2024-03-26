#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class ChessBoardArray {
 protected:
    class Row {
    public:
        Row(ChessBoardArray &a, int i) : board(a), row(i){}
        int & operator [] (int i) const{
            return board.select(row, i);
        }
    private:
        ChessBoardArray &board;
        int row;
    };

    class ConstRow {
    public:
         ConstRow(const ChessBoardArray &a, int i) : board(a), row(i){}
         const int operator [] (int i) const{
             return board.select(row, i);
         }
    private:
        const ChessBoardArray &board;
        int row;
    };

 public:
 ChessBoardArray(unsigned size = 0, unsigned b = 0){
    data = new int[(size*size+1)/2];
    base = b;
    length = size;
}
 ChessBoardArray(const ChessBoardArray &a){
    data = new int[(a.length*a.length+1)/2];
    base = a.base;
    length = a.length;
    for (unsigned i = 0; i<(length*length+1)/2; ++i) data[i] = a.data[i];
}
 ~ChessBoardArray(){
    delete [] data;
}

 ChessBoardArray & operator = (const ChessBoardArray &a) {
    delete [] data;
    base = a.base;
    length = a.length;
    data = new int[(length*length+1)/2];
    for (unsigned i = 0; i < (length*length+1)/2; ++i){
        data[i] = a.data[i];
    }
    return *this;
} 
    
 int & select(int i, int j){
    return data[loc(i,j)];
 }

 int select(int i, int j) const{
    return data[loc(i, j)];
}

 const Row operator [] (int i){
    return Row(*this, i);
}

 const ConstRow operator [] (int i) const{
    return ConstRow(*this, i);
}

int printData(){
    for (unsigned i = 0; i<(length*length+1)/2; ++i)cout << data[i] <<" ";
    cout << endl;
    return 0;
}

 friend ostream & operator << (ostream &out, const ChessBoardArray &a){
    for (int i=a.base; i<a.length+a.base; i++){
        for (int j=a.base; j<a.length+ a.base; j++){
                
                if ((i+j)%2 != 0) out << setw(4) << 0;
                else out << setw(4) << a[i][j];
            
        }
        
        out << endl;
    }
    return out;
}
 

protected:
    int *data;
    int base;
    unsigned length;
    unsigned loc(int i, int j) const throw(out_of_range){
        int di = i -base, dj = j - base;
        int s= di + dj;
        
        if (di >= length || di < 0 || dj >= length || dj<0) throw out_of_range("invalid index");
        if (s%2 == 1) throw out_of_range("the box is black");
        int n = di*(length/2) + dj/2;
        if (length%2 ==1) n = n+(di+1)/2;
        
        return n;
    }  
}; 

/*int main() {
 ChessBoardArray a(5, 2); // size 4x4, rows and columns numbered from 1
 a[3][5] = 42; 
 a[4][6] = 17;
 
 
 cout << a;
 }
 */

 

