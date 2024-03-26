#include <iostream>
using namespace std;


 class rational {
 public:

 rational (int n, int d = 1);

 friend rational operator + (const rational &x, const rational &y);
 friend rational operator - (const rational &x, const rational &y);
 friend rational operator * (const rational &x, const rational &y);
 friend rational operator / (const rational &x, const rational &y);

 friend std::ostream & operator << (std::ostream &out, const rational &x);

 private:
 int nom, den;

 static int gcd (int a, int b);
 };
 
 using namespace std;

 rational::rational (int n, int d) {
     nom = n; den = d;
 }
 rational operator + (const rational &x, const rational &y) {
     return rational (x.nom*y.den + x.den*y.nom, x.den*y.den);
 }

 rational operator - (const rational &x, const rational &y) {
     return rational (x.nom*y.den - x.den*y.nom, x.den*y.den);
 }

 rational operator * (const rational &x, const rational &y) {
     return rational (x.nom*y.nom, x.den*y.den);
 }

 rational operator / (const rational &x, const rational &y) {
     return rational (x.nom*y.den, x.den*y.nom);
 }

 ostream operator << (ostream &out, const rational &x){
     out << x.nom << "/" << x.den;
     return out;
 }

 int rational::gcd(int a, int b){
     if (a<0) a = -a;
     if (b<0) b = -b;

    while (a > 0 && b > 0){
        if (a > b) a%=b; else b%=a;
    }
return a + b;
 }
 

 
