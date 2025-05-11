#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "number6.h"

using namespace std;

long long pow_mod1(long long a, long long b, long long p) {
    long long result = 1;
    a %= p;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % p;
        b >>= 1;
        a = (a * a) % p;
    }
    return result;
}

vector<pair<long long, long long>> encrypt(const string& message, long long p, long long k, long long g, long long y) {
    vector<pair<long long, long long>> encrypted;
    for (char c : message) {
        long long m = static_cast<long long>(static_cast<unsigned char>(c));
        long long a = pow_mod1(g, k, p);
        long long b = (pow_mod1(y, k, p) * m) % p;
        encrypted.emplace_back(a, b);
    }
    return encrypted;
}

string decrypt(const vector<pair<long long, long long>>& encrypted, long long p, long long x) {
    string decrypted;
    for (const auto& pair : encrypted) {
        long long a = pair.first;
        long long b = pair.second;
        long long m = (b * pow_mod1(a, p-1-x, p)) % p;
        decrypted += static_cast<char>(m);
    }
    return decrypted;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return x < 0 ? x + m0 : x;
}

long long find_k(long long g, long long a, long long p) {
    long long current = 1;
    for (long long k = 0; k < p; ++k) {
        if (current == a) return k;
        current = (current * g) % p;
    }
    return -1;
}

string attack(const vector<pair<long long, long long>>& encrypted, long long p, long long g, long long y) {
    if (encrypted.empty()) return "";
    long long a = encrypted[0].first;
    for (const auto& pair : encrypted) 
        if (pair.first != a) {
            cout << "Атака невозможна: разные a.\n";
            return "";
        }
    long long k = find_k(g, a, p);
    if (k == -1) {
        cout << "k не найден.\n";
        return "";
    }
    long long s = pow_mod1(y, k, p);
    long long s_inv = mod_inverse(s, p);
    string result;
    for (const auto& pair : encrypted) {
        long long m = (pair.second * s_inv) % p;
        result += static_cast<char>(m);
    }
    return result;
}

void hacker() {
    long long p, k, g, x;
    cout << "Введите p (простое число): ";
    cin >> p;
    cout << "Введите k (cессионый ключ < p): ";
    cin >> k;
    cout << "Введите g (генератор < p): ";
    cin >> g;
    cout << "Введите x (закрытый ключ): ";
    cin >> x;
    cin.ignore();
    
    long long y = pow_mod1(g, x, p);
    cout << "Открытый ключ (y): " << y << endl;
    
    string message;
    cout << "Введите сообщение: ";
    getline(cin, message);
    
    auto encrypted = encrypt(message, p, k, g, y);
    
    cout << "Зашифрованное сообщение:\n";
    for (const auto& pair : encrypted)
        cout << "(" << pair.first << ", " << pair.second << ") ";
    cout << endl;
    
    string decrypted = decrypt(encrypted, p, x);
    cout << "Расшифрованое сообщение: " << decrypted << endl;
    
    cout << "\nЭмуляция атаки...\n";
    string attacked = attack(encrypted, p, g, y);
    if (!attacked.empty())
        cout << "Результат атаки: " << attacked << endl;
    

}