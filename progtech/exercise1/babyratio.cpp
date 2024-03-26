#include <iostream>
using namespace std;

 
class rational {
    
public:
rational (int n, int d);
rational add (rational r);
rational sub (rational r);
rational mul (rational r);
rational div (rational r);
void print ();


private:
int nom, den;	// nominator, denominator
static int gcd (int a, int b);

};


rational::rational (int n, int d) {
nom = n; den = d;
} 
 
rational rational::add (rational r) {

return rational (nom * r.den + den * r.nom, den * r.den);

}

rational rational::sub (rational r) {

return rational (nom * r.den - den * r.nom, den * r.den);

}

rational rational::mul (rational r) {

return rational (nom * r.nom, den * r.den);

}

rational rational::div (rational r) {

return rational (nom * r.den, den * r.nom);

}

void rational::print () {

int x, y;

x = nom/gcd(nom, den);
y = den/gcd(nom,den);

if ((x < 0 && y < 0) or (x>0 && y<0)) {
    x=-x; y=-y;
}
if (x==0 && y<0) y=-y;

cout << x << "/" << y;

} 
 
int rational::gcd (int a, int b) {
    
if (a<0) a = -a;
if (b<0) b = -b;

while (a > 0 && b > 0){
    if (a > b) a%=b; else b%=a;
}
return a + b;

}











