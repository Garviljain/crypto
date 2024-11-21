#include <bits/stdc++.h>
#include<unordered_set>
using namespace std;


vector<string> createBigraphs(string cipher) {
    vector<string> result;
    for (int i = 0; i < cipher.length(); i += 2) {
        result.push_back(cipher.substr(i, 2));
    }
    return result;
}


unordered_map<string, int> calcFreq(vector<string> bigraphs) {
    unordered_map<string, int> freqs;
    for (string b : bigraphs) {
        freqs[b]++;
    }
    return freqs;
}


double freqattack(unordered_map<string, int> obsFreqs, unordered_map<string, double> expFreqs, int total) {
    double result = 0;
    for (auto pair : expFreqs) {
        string bigraph = pair.first;
        double expCount = (pair.second * total) / 100;
        int obsCount = 0;
        if (obsFreqs.find(bigraph) != obsFreqs.end()) {
            obsCount = obsFreqs[bigraph];
        }
        result += pow(obsCount - expCount, 2) / expCount;
    }
    return result;
}


unordered_map<string, double> getExpectedFrequencies() {
    return {
    {"TH", 1.52}, {"HE", 1.28}, {"IN", 0.94}, {"ER", 0.94}, {"AN", 0.82},
    {"RE", 0.68}, {"ND",0.63},{"AT",0.59},{"ON", 0.57}, {"NT",0.56} ,{"HA",0.56}, {"ES",0.56},{"ST",0.55},  {"EN", 0.55}, {"ED", 0.53}, {"TO",0.52}, {"IT",0.50} ,{"OU",0.50}
    };
}


string playfairDecrypt(string cipher, vector<vector<char>> keyMatrix) {
    string plaintext = "";


    for (int i = 0; i < cipher.length(); i += 2) {
        char first = cipher[i];
        char second = cipher[i + 1];
        int r1, c1, r2, c2;


        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 5; ++c) {
                if (keyMatrix[r][c] == first) {
                    r1 = r;
                    c1 = c;
                }
                if (keyMatrix[r][c] == second) {
                    r2 = r;
                    c2 = c;
                }
            }
        }


        if (r1 == r2) {
            plaintext += keyMatrix[r1][(c1 + 4) % 5];
            plaintext += keyMatrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plaintext += keyMatrix[(r1 + 4) % 5][c1];
            plaintext += keyMatrix[(r2 + 4) % 5][c2];
        } else {
            plaintext += keyMatrix[r1][c2];
            plaintext += keyMatrix[r2][c1];
        }
    }


    return plaintext;
}


vector<vector<char>> generateKeyMatrix(string key) {
    vector<vector<char>> keyMatrix(5, vector<char>(5, ' '));
    unordered_set<char> used;
    int row = 0, col = 0;


    for (char ch : key) {
        if (used.find(ch) == used.end() && ch != 'J') {
            keyMatrix[row][col++] = ch;
            used.insert(ch);
            if (col == 5) {
                row++;
                col = 0;
            }
        }
    }


    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (used.find(ch) == used.end() && ch != 'J') {
            keyMatrix[row][col++] = ch;
            used.insert(ch);
            if (col == 5) {
                row++;
                col = 0;
            }
        }
    }


    return keyMatrix;
}


void freqAnalysisAttack(string cipher) {
    vector<string> bigraphs = createBigraphs(cipher);
    unordered_map<string, int> obsFreqs = calcFreq(bigraphs);
    unordered_map<string, double> expFreqs = getExpectedFrequencies();
    int totalBigraphs = bigraphs.size();


    vector<string> candidateKeys = { "EXAMPLE","MONARCHY", "KEYWORD"};
   
    string bestKey = "";
    string bestDecryption = "";
    double minChiSquare = INT_MAX;


    for (string candidateKey : candidateKeys) {
        vector<vector<char>> keyMatrix = generateKeyMatrix(candidateKey);
        string decryptedMessage = playfairDecrypt(cipher, keyMatrix);
        vector<string> decryptedBigraphs = createBigraphs(decryptedMessage);
        unordered_map<string, int> decryptedFreqs = calcFreq(decryptedBigraphs);


        double chiSquare = freqattack(decryptedFreqs, expFreqs, totalBigraphs);
       
        if (chiSquare < minChiSquare) {
            minChiSquare = chiSquare;
            bestKey = candidateKey;
            bestDecryption = decryptedMessage;
        }
    }


    cout << "Most likely key: " << bestKey << endl;
    cout << "Decrypted message: " << bestDecryption << endl;
    cout << "Chi-square value: " << minChiSquare << endl;
}


int main() {
    string cipher = "YELLQZOLAXW";
    freqAnalysisAttack(cipher);
    return 0;
}






