#include <iostream>
#include <tuple>
#include "math.h"
#include "crypto.h"
#include <cstdint>
#include <vector>
#include <unistd.h>

using namespace std;


enum class Option {
    FERMA = 1,
    EXTENDED_EUCLID,
    INVERSE_EUCLID,
    ELGAMAL, 
    CONTINUED_FRACTION,
    ATTACK_SIMULATION,
    EXIT = 0
};

int main() {
    int choice;
    do {
        cout << "\n1. Реализация a^x mod p через теорему Ферма\n";
        cout << "2. Алгоритм Евклида для вычисления с*d mod m=1 (через u и v)\n";
        cout << "3. Алгоритм Евклида для вычисления взаимообратного числа с^-1 mod m=d\n";
        cout << "4. Шифрование алгоритмом Эль-Гамаля\n";
        cout << "5. Решение уравнение через цепную дробь\n";
        cout << "6. Эмуляция атаки\n";
        cout << "0. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        

        try {
            switch(static_cast<Option>(choice)) {
                case Option::FERMA: {
                    try {
                        uint64_t a, x;
                        cout << "Введите с: ";
                        cin >> a;
                        cout << "Введите m: ";
                        cin >> x;
                        uint64_t p = input_prime("Введите p (должно быть простым): ");
                        while(true){

                            if (gcd(a, p) != 1) {
                                cerr << "a и p должны быть взаимно просты.";
                                continue;
                            }
                            break;
                        }

                        cout << "Результат (Ферма): " << fermat_method(a, x, p) << endl;
                        cout << "Результат (Бинарный): " << binary_exponentiation(a, x, p) << endl;

                        if (fermat_method(a, x, p) != binary_exponentiation(a, x, p)) {
                            cerr << "Алгоритмы дали разные результаты.";
                        } else {
                            cout << "Результаты совпадают!" << endl;
                        }
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case Option::EXTENDED_EUCLID: {
                    try {
                        int c, m;
                        cout << "Введите число c: ";
                        cin >> c;
                        cout << "Введите число m: ";
                        cin >> m;

                        auto result = Euclid(c, m);
                        cout << "u = " << get<1>(result) << ", v = " << get<2>(result) << endl;
                        cout << "Проверка: " << c << " * " << get<1>(result) << " + " << m << " * " << get<2>(result)
                             << " = " << c * get<1>(result) + m * get<2>(result) << endl;
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case Option::INVERSE_EUCLID: {
                    try {
                        int c, m;
                        cout << "Введите число c: ";
                        cin >> c;
                        cout << "Введите модуль m: ";
                        cin >> m;

                        auto [d, u, v] = Euclid(c, m);

                        if (d != 1) {
                            throw runtime_error("Обратного элемента не существует (НОД ≠ 1)");
                        }

                        int inverse = (u % m + m) % m;
                        cout << "Обратный элемент d = " << inverse << endl;
                        cout << c << "^-1 mod " << m << " = " << inverse << endl;
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case Option::ELGAMAL: {
                    try {
                        cout << "Введите значения для генерации открытого ключа" << endl;
                        uint64_t p = input_prime("Введите p (должно быть простым): ");
                        
                        uint64_t k = input_xkg("Введите k (случайное число < p): ", p);
                        uint64_t g = input_xkg("Введите g (случайное число < p): ", p);
                        uint64_t x = input_xkg("Введите x (случайное число < p): ", p);
                        cin.ignore();
                        uint64_t y = fast_pow(g, x, p);
                        cout << "Открытым ключом является значение: " << y << endl;

                        string message = getMessageFromUser();

                        auto encrypted = encrypt(message, p, k, g, y);
                        cout << "\nЗашифрованное сообщение:\n";
                        for (const auto& pair : encrypted) {
                            cout << "(" << pair.first << ", " << pair.second << ") ";
                        }
                        outputEncryptedMessage(encrypted);
                        string decrypted = decrypt(encrypted, p, x);
                        cout << "\nРасшифрованное сообщение: " << decrypted << endl;
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case Option::CONTINUED_FRACTION: {
                    try {
                        uint64_t p, q;
                        cin >> p;
                        cout << "/" << endl;
                        cin >> q;
                        vector<uint64_t> result = continuedFraction(p, q);
                        cout << p << "/" << q << " в виде цепной дроби = [";
                        for (size_t i = 0; i < result.size(); i++) {
                            cout << result[i];
                            if (i + 1 < result.size()) cout << ", ";
                        }
                        cout << "]" << endl;

                        cout << "\nРешение уравнения 1256a + 847b = 119 в целых числах:" << endl;
                        int a_coeff = 1256;
                        int b_coeff = 847;
                        int c = 119;

                        auto [gcd_val, x0, y0] = solveDiophantine(a_coeff, b_coeff, c);

                    cout << "Частное решение: a = " << x0 << ", b = " << y0 << endl;
                    cout << "Общее решение:" << endl;
                    cout << "a = " << x0 << " + " << (b_coeff / gcd_val) << " * k" << endl;
                    cout << "b = " << y0 << " - " << (a_coeff / gcd_val) << " * k" << endl;
                    cout << "где k — любое целое число." << endl;
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case Option::ATTACK_SIMULATION: {
                    try {
                        cout << "Введите значения для генерации открытого ключа" << endl;
                        uint64_t p = input_prime("Введите p (должно быть простым): ");
                        uint64_t k = input_xkg("Введите k (случайное число < p): ", p);
                        uint64_t g = input_xkg("Введите g (случайное число < p): ", p);
                        uint64_t x = input_xkg("Введите x (случайное число < p): ", p);
                        cin.ignore();
                        uint64_t y = fast_pow(g, x, p);
                        cout << "Открытым ключом является значение: " << y << endl;

                        string message = getMessageFromUser();

                        auto encrypted = encrypt(message, p, k, g, y);

                        cout << "Зашифрованное сообщение:\n";
                        for (const auto& pair : encrypted)
                            cout << "(" << pair.first << ", " << pair.second << ") ";
                        cout << endl;

                        cout << "\nЭмуляция атаки...\n";
                        string attacked = attack(encrypted, p, g, y);
                        if (!attacked.empty())
                            cout << "Результат атаки: " << attacked << endl;
                            
                    } catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                    break;
                } 
                case Option::EXIT:
                    cout << "Выход из программы...\n";
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (...) {
            cout << "Ошибка ввода" << endl;
        }
        sleep(2);
    } while(choice != 0);

    return 0;
}