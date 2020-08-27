#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>


using namespace std;

typedef unsigned long long int lli;


lli gcd(lli a, lli b);

lli gcdExtended(lli a, lli b, int* x, int* y);

lli Mod_Mul(lli a, lli b, lli c);

lli Mod_Exp(lli base, lli exponent, lli mod);

bool is_prime(lli p, int iteration);

void To_ASCII(string infile, string outfile);

void From_ASCII(string infile, string outfile);

void RSA_Encryption(string infile, string outfile, lli e, lli n);

void RSA_Decryption(string infile, string outfile, lli e, lli n);


int main() {

    srand(time(NULL));

    lli p, q, n, k, e, d;
    int x, y;
    int j = 5;  // number of Miller iteration
    
    //Generating primes p and q randomly
    p = rand() % 1000000; // restricting random number to 999999 to prevent memory overflow
    q = rand() % 1000000;

    if (p % 2 == 0)
        p++;

    if (q % 2 == 0)
        q++;

    while (!is_prime(p, j))
        p += 2;
    
    while (!is_prime(q, j))
        q += 2;
    
    
    
    //Computing k and n
    n = p * q;
    k = (p - 1) * (q - 1);
    
    
    // Generating e
    do {
        e = rand() %k;
    } while (gcd(e,k)!=1);


    
    //computing d using the extende Ecludian algorithm
    lli temp = gcdExtended(k, e, &x, &y);
    if (y < 0) {
        y += k;
    }
    d = y;



    cout<< "first prime number p is: " << p << endl;
    cout << "second prime number q is: " << q << endl;
    cout << "n= p * q is: " << n << endl;
    cout << "k = (p - 1) * (q - 1) is: "<< k << endl;
    cout << "e is: " << e << endl;
    //cout << "gcd(k,e)=: " << gcd(k, e) << endl;
    //cout << x << "  " << y<< endl;
    //cout << x * k + y * e << endl;

   cout << "d is " << d << endl;
   //cout << "d*e mod k is: " << (d*e)%k << endl;
    To_ASCII("Text.txt", "ASCII.txt");
    RSA_Encryption("ASCII.txt", "Encryption.txt", e, n);
    RSA_Decryption("Encryption.txt", "ASCII2.txt", d, n);
    From_ASCII("ASCII2.txt", "Decryption.txt");

}
///////////////////////////////////////////////////////////////////////////////////////
// gcd of a and b 
lli gcd(lli a, lli b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}


lli gcdExtended(lli a, lli b, int* x, int* y)
{
    // Base Case  
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call  
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of  
    // recursive call  
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}


//Computes (a * b) mod c
lli Mod_Mul(lli a, lli b, lli c)
{

    return ((a % c) * (b % c)) % c;
    // lli res = 0;
    // a = a % c;
    /* while (b > 0)
     {
         if (b % 2 == 1)
             res = (res + a) % c;
         a = (a * 2) % c;
         b /= 2;
     }
     return res % c;*/
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



void To_ASCII(string infile, string outfile)
{
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile);
    outFile.open(outfile);
    if (!inFile || !outFile) {
        cout << "Error opening one of the files" << std::endl;
        return;
    }
    while (!inFile.eof()) {
        char charchter;

        inFile.get(charchter);
        int a = charchter;
        outFile << a;
        outFile << endl;
        //cout << a;
    }
    std::cout << "To_ASCII finished successfully" << std::endl;
    inFile.close();
    outFile.close();

}
void From_ASCII(string infile, string outfile) {
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile);
    outFile.open(outfile);
    if (!inFile || !outFile) {
        cout << "Error opening one of the files" << std::endl;
        return;
    }
    while (!inFile.eof()) {
        int a;

        inFile >> a;
        char charecter = a;
        outFile << charecter;
        //outFile << endl;
         //cout << a;
    }
    cout << "From_ASCII finished successfully" << std::endl;
    inFile.close();
    outFile.close();
}



void RSA_Encryption(string infile, string outfile, lli e, lli n) {
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile);
    outFile.open(outfile);


    while (!inFile.eof()) {
        lli m;

        inFile >> m;
        lli c = Mod_Exp(m, e, n);
        outFile << c;
        outFile << endl;
        //cout << a;
    }
    std::cout << "Encryption finished successfully" << std::endl;
    inFile.close();
    outFile.close();
}


void RSA_Decryption(string infile, string outfile, lli d, lli n) {
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile);
    outFile.open(outfile);


    while (!inFile.eof()) {
        lli c;

        inFile >> c;
        lli m = Mod_Exp(c, d, n);
        outFile << m;
        outFile << endl;
        //cout << a;
    }
    std::cout << "Decryption finished successfully" << std::endl;
    inFile.close();
    outFile.close();
}