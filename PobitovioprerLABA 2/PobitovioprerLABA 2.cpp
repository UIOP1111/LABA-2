#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;


unsigned add(unsigned a, unsigned b) {
    while (b != 0) {
        unsigned carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}


unsigned negate(unsigned x) {
    return add(~x, 1);
}


unsigned sub(unsigned a, unsigned b) {
    return add(a, negate(b));
}


unsigned mul(unsigned a, unsigned b) {
    unsigned result = 0;
    while (b != 0) {
        if (b & 1) result = add(result, a); 
        a <<= 1;                            
        b >>= 1;                   
    }
    return result;
}


unsigned divide(unsigned n, unsigned d, unsigned& rem) {
    unsigned q = 0, r = 0;
    for (unsigned bit = 1u << 31; bit != 0; bit >>= 1) {
        unsigned overflow = r >> 31;          
        r = (r << 1) | ((n & bit) ? 1u : 0u); 
        if (overflow || r >= d) {             
            r = sub(r, d);
            q |= bit;                         
        }
    }
    rem = r;
    return q;
}

unsigned to_u(int x) { return static_cast<unsigned>(x); }
int      to_i(unsigned x) { return static_cast<int>(x); }
bool     is_neg(int x) { return (to_u(x) >> 31) != 0; }
unsigned abs_u(int x) { return is_neg(x) ? negate(to_u(x)) : to_u(x); }

int int_add(int a, int b) { return to_i(add(to_u(a), to_u(b))); }
int int_sub(int a, int b) { return to_i(sub(to_u(a), to_u(b))); }
int int_mul(int a, int b) { return to_i(mul(to_u(a), to_u(b))); }

int int_div(int a, int b) {
    unsigned rem;
    unsigned q = divide(abs_u(a), abs_u(b), rem);
    return to_i(is_neg(a) != is_neg(b) ? negate(q) : q);
}

int main() {
    int a, b , c ,d;
    cout << "Enter 4 numbers: ";
    cin >> a >> b >> c >> d;
	int f3 = int_add(int_mul(-65, a), int_mul(d, 14));
    int f1 = int_mul(303, b);
    int f2 = int_add(int_mul(d, 15), int_mul(12, c));
	int f4 = int_div(f2, 512);
	int f5 = int_add(f1, f3);
	int f6 = int_add(f5, f4);
	cout << "Result: " << f6 << endl;
    //cout << int_sub(int_add((int_mul(303, b)), int_div(int_add(int_mul(d, 15), int_mul(12, c)), 512)) , int_add(int_mul(65,a), int_mul(d,14)));
    
}