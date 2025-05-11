#include <iostream>
#include <vector>
using namespace std; 
long long pow_mod1(long long a, long long b, long long p);
vector<pair<long long, long long>> encrypt(const string& message, long long p, long long k, long long g, long long y);
string decrypt(const vector<pair<long long, long long>>& encrypted, long long p, long long x);
long long mod_inverse(long long a, long long m);
long long find_k(long long g, long long a, long long p);
string attack(const vector<pair<long long, long long>>& encrypted, long long p, long long g, long long y);
void hacker();