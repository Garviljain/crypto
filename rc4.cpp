#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Key Scheduling Algorithm
void KSA(vector<int>& S, const vector<int>& key) {
    int j = 0;
    int keyLen = key.size();
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keyLen]) % 256;
        swap(S[i], S[j]);
    }
}

// Pseudo-Random Generation Algorithm
vector<int> PRGA(const vector<int>& S, int messageLen) {
    vector<int> keystream(messageLen);
    int i = 0, j = 0;
    vector<int> S_copy = S; // Copy of S to avoid modifying it
    for (int k = 0; k < messageLen; k++) {
        i = (i + 1) % 256;
        j = (j + S_copy[i]) % 256;
        swap(S_copy[i], S_copy[j]);
        keystream[k] = S_copy[(S_copy[i] + S_copy[j]) % 256];
    }
    return keystream;
}

void measurePerformance(int keyLength, int messageLength) {
    vector<int> S(256);
    vector<int> key(keyLength, 1); // Example key: all 1s

    // Measure KSA time
    auto start = chrono::high_resolution_clock::now();
    KSA(S, key);
    auto end = chrono::high_resolution_clock::now();
    auto ksaTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Measure PRGA time
    start = chrono::high_resolution_clock::now();
    vector<int> keystream = PRGA(S, messageLength);
    end = chrono::high_resolution_clock::now();
    auto prgaTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Output results
    cout << "Key Length: " << keyLength << " bits, "
         << "Message Length: " << messageLength << " bytes\n";
    cout << "KSA Time: " << ksaTime << " microseconds\n";
    cout << "PRGA Time: " << prgaTime << " microseconds\n\n";
}

int main() {
    measurePerformance(40, 1024);   // 1 KB with 40-bit key
    measurePerformance(128, 10240); // 10 KB with 128-bit key
    measurePerformance(256, 1048576); // 1 MB with 256-bit key

    return 0;
}
