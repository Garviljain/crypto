#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// AES S-Box (Empty Placeholder)
const uint8_t SBox[16][16] = {};

// Substitute Bytes (SubBytes) step
void subBytes(vector<vector<uint8_t>>& state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            uint8_t value = state[i][j];
            uint8_t row = (value >> 4) & 0x0F;
            uint8_t col = value & 0x0F;
            state[i][j] = SBox[row][col];
        }
    }
}

// Shift Rows step
void shiftRows(vector<vector<uint8_t>>& state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].begin(), state[i].begin() + i, state[i].end());
    }
}

// Add Round Key step
void addRoundKey(vector<vector<uint8_t>>& state, const vector<vector<uint8_t>>& roundKey) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] ^= roundKey[i][j];
        }
    }
}

// AES single-round encryption
vector<vector<uint8_t>> aesEncrypt(vector<vector<uint8_t>> plaintext, vector<vector<uint8_t>> key) {
    // Initial round key addition
    addRoundKey(plaintext, key);

    // SubBytes step
    subBytes(plaintext);

    // ShiftRows step
    shiftRows(plaintext);

    // AddRoundKey step
    addRoundKey(plaintext, key);

    return plaintext;
}

// Display the state matrix
void printState(const vector<vector<uint8_t>>& state) {
    for (const auto& row : state) {
        for (const auto& value : row) {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(value) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main() {
    // Example 4x4 plaintext matrix (128-bit plaintext)
    vector<vector<uint8_t>> plaintext = {
        {0x32, 0x43, 0xf6, 0xa8},
        {0x88, 0x5a, 0x30, 0x8d},
        {0x31, 0x31, 0x98, 0xa2},
        {0xe0, 0x37, 0x07, 0x34}
    };

    // Example 4x4 key matrix (128-bit key)
    vector<vector<uint8_t>> key = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };

    cout << "Original Plaintext Matrix:" << endl;
    printState(plaintext);

    cout << "Encryption Key Matrix:" << endl;
    printState(key);

    // Perform encryption
    vector<vector<uint8_t>> encrypted = aesEncrypt(plaintext, key);

    cout << "Encrypted Matrix After One AES Round:" << endl;
    printState(encrypted);

    return 0;
}

