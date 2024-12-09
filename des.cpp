#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// Permutation function
string permute(string input, int* permutationTable, int size) {
    string output = "";
    for (int i = 0; i < size; i++) {
        output += input[permutationTable[i] - 1];
    }
    return output;
}

// XOR operation
string XOR(string a, string b) {
    string result = "";
    for (size_t i = 0; i < a.size(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Simplified DES S-Box
string sBox(string input) {
    int sBoxTable[4][4] = {
        {3, 2, 1, 0},
        {0, 1, 2, 3},
        {3, 0, 1, 2},
        {2, 1, 0, 3}
    };
    int row = bitset<2>(input.substr(0, 2)).to_ulong();
    int col = bitset<2>(input.substr(2, 2)).to_ulong();
    int value = sBoxTable[row][col];
    return bitset<2>(value).to_string();
}

// Feistel function
string feistelFunction(string right, string subKey) {
    // Expansion permutation
    int expansionTable[4] = {4, 1, 2, 3};
    string expandedRight = permute(right, expansionTable, 4);

    // XOR with subKey
    string xored = XOR(expandedRight, subKey);

    // S-Box substitution
    string sBoxOutput = sBox(xored.substr(0, 4)) + sBox(xored.substr(4, 4));

    // Permutation after S-Box
    int permutationTable[4] = {2, 4, 3, 1};
    return permute(sBoxOutput, permutationTable, 4);
}

// Simplified DES encryption
string simplifiedDES(string plaintext, string key) {
    // Initial permutation
    int initialPermutation[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    string permutedText = permute(plaintext, initialPermutation, 8);

    // Split into left and right halves
    string left = permutedText.substr(0, 4);
    string right = permutedText.substr(4, 4);

    // Subkey generation
    string subKey1 = key.substr(0, 8);
    string subKey2 = key.substr(8, 8);

    // Round 1
    string tempRight = right;
    right = XOR(left, feistelFunction(right, subKey1));
    left = tempRight;

    // Round 2
    tempRight = right;
    right = XOR(left, feistelFunction(right, subKey2));
    left = tempRight;

    // Combine left and right
    string combined = right + left;

    // Final permutation
    int finalPermutation[8] = {4, 1, 3, 5, 7, 2, 8, 6};
    return permute(combined, finalPermutation, 8);
}

int main() {
    string plaintext = "11010111"; // 8-bit plaintext
    string key = "1010000010";    // 10-bit key

    string encrypted = simplifiedDES(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    return 0;
}
