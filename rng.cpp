#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cassert>

std::vector<uint8_t> generate_key(size_t length) {
    std::vector<uint8_t> key(length);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
   
    for (auto &byte : key) {
        byte = static_cast<uint8_t>(dis(gen));
    }
   
    return key;
}


std::vector<uint8_t> xor_vectors(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    assert(a.size() == b.size());
    std::vector<uint8_t> result(a.size());
   
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }
   
    return result;
}


void print_hex(const std::vector<uint8_t>& vec) {
    for (auto byte : vec) {
        std::cout << static_cast<int>(byte);
    }
    std::cout << std::dec << std::endl;
}

void one_time_pad(std::string& inp){
while(inp.size()%32){
inp.push_back('0');
}
}

int main() {
   
    const size_t key_size = 32; // 256 bits = 32 bytes

   
    std::vector<uint8_t> key = generate_key(key_size);
    std::cout << "Key: ";
    print_hex(key);

   
    std::string plaintext_str = "This is a 32-byte text!" ;
    one_time_pad(plaintext_str);
    std::vector<uint8_t> plaintext(plaintext_str.begin(), plaintext_str.end());


   

 
    std::vector<uint8_t> ciphertext = xor_vectors(plaintext, key);
    std::cout << "Ciphertext: ";
    print_hex(ciphertext);

   
    std::vector<uint8_t> decrypted_plaintext = xor_vectors(ciphertext, key);
    std::string decrypted_str(decrypted_plaintext.begin(), decrypted_plaintext.end());
   
    std::cout << "Decrypted Plaintext: " << decrypted_str << std::endl;

    return 0;
}
