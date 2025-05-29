#include <vector>
#include <iostream>
#include <map>
#include <cstdint>
#include <cmath>
#include <fstream>
#include "math.h"
#include "crypto.h"

using namespace std;
vector<pair<int64_t, int64_t >> encrypt(const string& message, int64_t p, int64_t k, int64_t g, int64_t y) {
    vector<pair<int64_t, int64_t>> encrypted;
    for (char c : message) {
        int64_t m = static_cast<int64_t >(static_cast<unsigned char>(c)); 
        int64_t a = fast_pow(g, k, p);
        int64_t b = (fast_pow(y, k, p) * m) % p;
        encrypted.emplace_back(a, b);
    }
    return encrypted;
}
// Функция дешифрования
string decrypt(const vector<pair<int64_t, int64_t>>& encrypted, int64_t p, int64_t x) {
    string decrypted;
    for (const auto& pair : encrypted) {
        int64_t a = pair.first;
        int64_t b = pair.second;
        int64_t exponent = p - 1 - x;
        int64_t a_pow = fast_pow(a, exponent, p);
        int64_t m = (b * a_pow) % p;
        decrypted += static_cast<char>(m);
    }
    return decrypted;
}
int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t m0 = m, y = 0, x = 1;

    if (m == 1) return 0; 

    while (a > 1) {
        int64_t q = a / m;

        int64_t t = m;
        m = a % m;
        a = t;

        t = y;
        y = x - q * y;
        x = t;
    }

    return x < 0 ? x + m0 : x;
}
int64_t find_k(int64_t g, int64_t a, int64_t p) {
    int64_t n = static_cast<int64_t>(sqrt(p)) + 1;

    // Таблица для g^(1 * i) % p
    map<int64_t, int64_t> values;
    int64_t current = 1;
    for (int64_t i = 0; i < n; ++i) {
        values[current] = i;
        current = (current * g) % p;
    }

    // g^(-n) % p
    int64_t factor = fast_pow(g, p - 1 - n, p);
    current = a;

    for (int64_t j = 0; j < n; ++j) {
        if (values.count(current)) {
            return j * n + values[current];
        }
        current = (current * factor) % p;
    }
    return -1;
}

string attack(const vector<pair<int64_t , int64_t  >>& encrypted, int64_t   p, int64_t   g, int64_t  y) {
    if (encrypted.empty()) return "";
    int64_t  a = encrypted[0].first;
    for (const auto& pair : encrypted) 
        if (pair.first != a) {
            cout << "Атака невозможна: разные a.\n";
            return "";
        }
    int64_t  k = find_k(g, a, p);
    if (k == -1) {
        cout << "k не найден.\n";
        return "";
    }
    int64_t  s = fast_pow(y, k, p);
    int64_t  s_inv = mod_inverse(s, p);
    string result;
    for (const auto& pair : encrypted) {
        int64_t  m = (pair.second * s_inv) % p;
        result += static_cast<char>(m);
    }
    return result;
}
string readMessageFromFile(const string& filename) {
    ifstream file(filename, ios::binary); // открываем 
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл " + filename);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // чтение
    file.close();
    return content;
}

// Функция для записи зашифрованных данных в файл
void writeEncryptedToFile(const string& filename, const vector<pair<int64_t , int64_t >>& encrypted) {
    ofstream file(filename); // создаем
    if (!file.is_open()) {
        throw runtime_error("Не удалось создать файл " + filename);
    }
    for (const auto& pair : encrypted) {
        file << pair.first << " " << pair.second << " ";
    }
    if (!file.good()) {
        throw runtime_error("Ошибка записи в файл " + filename);
    }
    file.close();
}

string getMessageFromUser() {
    int sourceChoice;
    string message;
    
    cout << "\nВыберите источник сообщения:\n";
    cout << "1 - Ввод с клавиатуры\n";
    cout << "2 - Чтение из файла\n";
    cout << "Ваш выбор: ";
    
    if (!(cin >> sourceChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка потока
        throw runtime_error("Ошибка ввода выбора источника");
    }
    cin.ignore();
    
    if (sourceChoice == 1) {
        cout << "Введите сообщение для шифрования: ";
        getline(cin, message);
    } 
    else if (sourceChoice == 2) {
        string filename;
        cout << "Введите имя файла с сообщением: ";
        getline(cin, filename);
        message = readMessageFromFile(filename);
    } 
    else {
        throw runtime_error("Неверный выбор источника сообщения");
    }
    
    return message;
}

void outputEncryptedMessage(const vector<pair<int64_t , int64_t >>& encrypted) {
    int outputChoice;
    cout << "\nВыберите способ вывода зашифрованного сообщения:\n";
    cout << "1 - Вывод на экран\n";
    cout << "2 - Сохранение в файл\n";
    cout << "3 - И то, и другое\n";
    cout << "Ваш выбор: ";
    
    if (!(cin >> outputChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Ошибка ввода выбора вывода");
    }
    cin.ignore();
    
    if (outputChoice == 1 || outputChoice == 3) {
        cout << "\nЗашифрованное сообщение:\n";
        for (const auto& pair : encrypted) {
            cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        cout << endl;
    }
    
    if (outputChoice == 2 || outputChoice == 3) {
        string filename;
        cout << "Введите имя файла для сохранения: ";
        getline(cin, filename);
        writeEncryptedToFile(filename, encrypted);
        cout << "Зашифрованные данные сохранены в файл " << filename << endl;
    }
}
uint64_t input_xkg(const string& prompt, uint64_t max_value) {
    uint64_t value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (value < max_value) {
            return value;
        }
        cerr << "Ошибка: значение должно быть меньше " << max_value << "!\n";
    }
}