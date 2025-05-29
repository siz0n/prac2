#include <tuple> 
#include <vector>
#include <cstdint>
#include <iostream>
using namespace std;
tuple<uint64_t, uint64_t , uint64_t > Euclid(uint64_t c, uint64_t m);// 
bool is_prime(int64_t n);
uint64_t gcd(uint64_t a, uint64_t b);
uint64_t fast_pow(uint64_t a, uint64_t x, uint64_t p );
uint64_t binary_exponentiation(int64_t a, int64_t x,int64_t p);
uint64_t fermat_method(uint64_t a, uint64_t x, uint64_t p);
vector<uint64_t > continuedFraction(uint64_t   p, uint64_t  q);
uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t mod);
uint64_t input_prime(const string& outas);
tuple<int64_t, int64_t, int64_t> solveDiophantine(int64_t a, int64_t b, int64_t c);