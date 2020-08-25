#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef unsigned long long int lli;

lli generate_prime() {
    lli c = rand() % 1000000;
    if (c % 2 == 0)
        c++;
    return 0;
}

//Computes (a * b) mod c
lli Mod_Mul(lli a, lli b, lli c)
{
    lli res = 0;
    a = a % c;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res + a) % c;
        a = (a * 2) % c;
        b /= 2;
    }
    return res % c;
}

lli Mod_Exp(lli base, lli exponent, lli mod) {

    if (mod == 0)
        return 0;

    base %= mod;
    lli res = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            res = Mod_Mul(res, base, mod);
        base = Mod_Mul(base, base, mod);
        exponent /= 2;
    }
    return res;
}

//Miller - Rabin Primality test, iteration signifies the accuracy

bool is_prime(lli p, int iteration)
{

    int i;
    lli s;
    if (p < 2)
    {
        return 0;
    }
    if (p != 2 && p % 2 == 0)
    {
        return 0;
    }
    s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (i = 0; i < iteration; i++)
    {
        long long a = rand() % (p - 1) + 1, temp = s;
        long long mod = Mod_Exp(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = Mod_Mul(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main() {
    srand(time(NULL));

    lli p, q, n, k, e;
    int j = 5;

    //Generating primes p and q randomly
    do {
        p = rand() % 1000000; // restricting random number to 999999 to prevent memory overflow
    } while (!is_prime(p,j));

    do {
        q = rand() % 1000000;
    } while (!is_prime(q,j));

    //Computing phi and n
    n = p * q;
    k = (p - 1) * (q - 1);
    cout<< "first prime number p is: " << p << endl;
    cout << "second prime number q is: " << q << endl;
    cout << "n= p * q is: " << n << endl;
    cout << " k = (p - 1) * (q - 1) is: "<< k << endl;


    //cout << Mod_Mul(5, 2, 7)<<endl;
    //cout << Mod_Exp(5, 7, 7) << endl;
    //cout << is_prime(67,5);

}