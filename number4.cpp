#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "number4.h"
using namespace std;

// Быстрое возведение в степень по модулю
long long pow_mod(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % p;
        b = b >> 1;
        a = (a * a) % p;
    }
    return result;
}

// Функция шифрования
vector<pair<long long, long long>> encrypt1(const string& message, long long p, long long k, long long g, long long y) {
    vector<pair<long long, long long>> encrypted;
    for (char c : message) {
        long long m = static_cast<long long>(static_cast<unsigned char>(c)); // Исправлено здесь
        long long a = pow_mod(g, k, p);
        long long b = (pow_mod(y, k, p) * m) % p;
        encrypted.emplace_back(a, b);
    }
    return encrypted;
}
// Функция дешифрования
string decrypt1(const vector<pair<long long, long long>>& encrypted, long long p, long long x) {
    string decrypted;
    for (const auto& pair : encrypted) {
        long long a = pair.first;
        long long b = pair.second;
        long long exponent = p - 1 - x;
        long long a_pow = pow_mod(a, exponent, p);
        long long m = (b * a_pow) % p;
        decrypted += static_cast<char>(m);
    }
    return decrypted;
}

void shifr() {
    long long p, k, g, x;
    
    // Ввод параметров
    cout << "Введите значения для генерации открытого ключа" << endl;;
    cout << "Введите p (простое число): ";
    cin >> p;
    cout << "Введите k (случайное число<p): ";
    cin >> k;
    cout << "Введите g (генератор < p): ";
    cin >> g;
    cout << "Введите x (закрытый ключ): ";
    cin >> x;
    cin.ignore();
    
    
    // Вычисление открытого ключа
    long long y = pow_mod(g, x, p);
    cout << "Открытым ключом является значение: "<< y << endl;
    
    // Ввод сообщения
    string message;
    cout << "Введите сообщение для шифрования: ";
    getline(cin, message);
    
    // Шифрование
    auto encrypted = encrypt1(message, p, k, g, y);
    
    // Вывод зашифрованных данных
    cout << "\nЗашифрованное сообщение:\n";
    for (const auto& pair : encrypted) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    
    
    // Дешифрование
    string decrypted = decrypt1(encrypted, p, x);
    
    // Вывод результатов
    cout << "\nРасшифрованное сообщение: " << decrypted << endl;
    
}