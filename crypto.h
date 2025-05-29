#include <vector>
#include <iostream>
#include <cstdint>



using namespace std;
vector<pair<int64_t , int64_t >> encrypt(const string& message, int64_t  p, int64_t  k, int64_t  g, int64_t  y);
string decrypt(const vector<pair<int64_t , int64_t >>& encrypted, int64_t  p, int64_t  x);
int64_t  mod_inverse(int64_t  a, int64_t  m);
string attack(const vector<pair<int64_t , int64_t >>& encrypted, int64_t  p, int64_t  g, int64_t  y);
int64_t  find_k(int64_t  g, int64_t  a, int64_t  p);
string readMessageFromFile(const string& filename);
void writeEncryptedToFile(const string& filename, const vector<pair<int64_t , int64_t >>& encrypted);
string getMessageFromUser();
void outputEncryptedMessage(const vector<pair<int64_t , int64_t >>& encrypted);
uint64_t input_xkg(const string& prompt, uint64_t max_value);