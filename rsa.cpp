#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Function to calculate gcd
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd
            result = (result * base) % mod;
        exp = exp >> 1;  // exp = exp / 2
        base = (base * base) % mod;
    }
    return result;
}

// Function to find modular inverse
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1; // No inverse found
}

int main() {
    // Step 1: Choose two prime numbers
    int p = 61; // Example prime number
    int q = 53; // Example prime number
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Step 2: Choose public key exponent e
    int e = 17; // e must be coprime with phi and 1 < e < phi
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Step 3: Calculate private key d
    int d = modInverse(e, phi);

    // Display keys
    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;

    // Step 4: Encryption
    int plainText = 65; // Example message
    long long cipherText = modExp(plainText, e, n);
    cout << "Encrypted Message: " << cipherText << endl;

    // Step 5: Decryption
    long long decryptedText = modExp(cipherText, d, n);
    cout << "Decrypted Message: " << decryptedText << endl;

    return 0;
}
