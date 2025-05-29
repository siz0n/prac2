#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

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
vector<pair<long long, long long>> encrypt(const string& message, long long p, long long k, long long g, long long y) {
    vector<pair<long long, long long>> encrypted;
    for (char c : message) {
        long long m = static_cast<long long>(static_cast<unsigned char>(c));
        long long a = pow_mod(g, k, p);
        long long b = (pow_mod(y, k, p) * m) % p;
        encrypted.emplace_back(a, b);
    }
    return encrypted;
}

// Функция дешифрования
string decrypt(const vector<pair<long long, long long>>& encrypted, long long p, long long x) {
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

// Функция для чтения сообщения из файла
string readMessageFromFile(const string& filename) {
    ifstream file(filename, ios::binary); // открываем в бинарном режиме
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл " + filename);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Функция для записи зашифрованных данных в файл
void writeEncryptedToFile(const string& filename, const vector<pair<long long, long long>>& encrypted) {
    ofstream file(filename);
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void outputEncryptedMessage(const vector<pair<long long, long long>>& encrypted) {
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

int main() {
    try {
        long long p, k, g, x;
        
        // Ввод параметров с клавиатуры
        cout << "Введите параметры для шифрования:" << endl;
        cout << "Введите p (простое число): ";
        if (!(cin >> p)) throw runtime_error("Некорректный ввод p");
        
        cout << "Введите k (случайное число < p): ";
        if (!(cin >> k)) throw runtime_error("Некорректный ввод k");
        
        cout << "Введите g (генератор < p): ";
        if (!(cin >> g)) throw runtime_error("Некорректный ввод g");
        
        cout << "Введите x (закрытый ключ): ";
        if (!(cin >> x)) throw runtime_error("Некорректный ввод x");
        
        cin.ignore(); // Очистка буфера после ввода чисел
        
        // Вычисление открытого ключа
        long long y = pow_mod(g, x, p);
        cout << "\nОткрытый ключ (y): " << y << endl;
        
        // Выбор источника сообщения
        string message = getMessageFromUser();
        
        auto encrypted = encrypt(message, p, k, g, y);
        
        outputEncryptedMessage(encrypted);
        
        // Дешифрование и вывод результата
        string decrypted = decrypt(encrypted, p, x);
        cout << "\nРасшифрованное сообщение: " << decrypted << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}