
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// Function to generate an LFSR sequence
vector<int> generateLFSR(const vector<int>& feedbackPoly, vector<int> seed, int numBits) {
    vector<int> output;
    int n = feedbackPoly.size();
    for (int i = 0; i < numBits; i++) {
        // XOR the feedback taps
        int newBit = 0;
        for (int j = 0; j < n; j++) {
            if (feedbackPoly[j] == 1) {
                newBit ^= seed[j];
            }
        }
        // Shift and insert the new bit
        output.push_back(seed.back());
        for (int j = n - 1; j > 0; j--) {
            seed[j] = seed[j - 1];
        }
        seed[0] = newBit;
    }
    return output;
}

// Print the sequence
void printSequence(const vector<int>& seq) {
    for (int bit : seq) {
        cout << bit;
    }
    cout << endl;
}

int main() {
    vector<int> feedbackPoly = {1, 0, 1}; // x^2 + 1
    vector<int> seed = {1, 0};           // Initial seed
    int numBits = 20;

    cout << "LFSR Sequence: ";
    vector<int> sequence = generateLFSR(feedbackPoly, seed, numBits);
    printSequence(sequence);

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

vector<int> recoverFeedbackPoly(const vector<int>& observed, int n) {
    vector<vector<int>> equations(n, vector<int>(n, 0));
    vector<int> results(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            equations[i][j] = observed[i + j];
        }
        results[i] = observed[i + n];
    }
    vector<int> feedbackPoly(n, 0);
    for (int i = 0; i < n; i++) {
        if (equations[i][i] == 0) {
            for (int k = i + 1; k < n; k++) {
                if (equations[k][i] == 1) {
                    swap(equations[i], equations[k]);
                    swap(results[i], results[k]);
                    break;
                }
            }
        }
        for (int k = i + 1; k < n; k++) {
            if (equations[k][i] == 1) {
                for (int j = i; j < n; j++) {
                    equations[k][j] ^= equations[i][j];
                }
                results[k] ^= results[i];
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        feedbackPoly[i] = results[i];
        for (int j = i + 1; j < n; j++) {
            feedbackPoly[i] ^= equations[i][j] * feedbackPoly[j];
        }
    }
    return feedbackPoly;
}

int main() {
    vector<int> observed = {1, 0, 1, 1, 0, 1};
    int n = 3;
    vector<int> feedbackPoly = recoverFeedbackPoly(observed, n);
    for (int bit : feedbackPoly) {
        cout << bit << " ";
    }
    cout << endl;
    return 0;
}




