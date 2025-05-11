#include <iostream>
#include <vector>
using namespace std;

long long pow_mod(long long a, long long b, long long p);
vector<pair<long long, long long>> encrypt1(const string& message, long long p, long long k, long long g, long long y);
string decrypt1(const vector<pair<long long, long long>>& encrypted, long long p, long long x);
void shifr();