#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// --- 1. Проверка простоты числа ---
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// --- 2. Алгоритм Евклида для НОД ---
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// --- 3. Быстрое возведение в степень по модулю 
int fast_pow(int a, int x, int p ){
    int result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * a) % p;
        }
        x = x / 2; 
        a = (a * a) % p;
    }
    return result;
}

// --- 4. Алгоритм через теорему Ферма ---
int fermat_method(int a, int x, int p) {
    int new_x = x % (p - 1);
    return fast_pow(a, x, p);
}

// --- 5. Алгоритм через бинарное разложение 
int binary_exponentiation(int a, int x, int p) {
        if (p <= 1) return 0; // Некорректный модуль
        if (x == 0) return 1 % p; // a^0 mod p = 1 (при p > 1)
        
        long long result = 1;
        a = a % p; // Гарантируем, что a < p
        
        while (x > 0) {
            // Если текущий бит x нечётный, умножаем результат на a
            if (x & 1) {
                result = (result * a) % p;
            }
            
            a = (a * a) % p;
            // Переходим к следующему биту
            x /= 2;
        }
        return result;
    }

// --- Основная программа ---
void exponentiationDemo() {
    int a, x, p;

    cout << "Введите a: ";
    cin >> a;
    cout << "Введите x: ";
    cin >> x;
    cout << "Введите p: ";
    cin >> p;

    if (!is_prime(p)) {
        cerr << "Ошибка: p должно быть простым!\n";
        
    }

    if (gcd(a, p) != 1) {
        cerr << "Ошибка: a и p должны быть взаимно просты!\n";
        
    }

    int result_fermat = fermat_method(a, x, p);
    int result_binary = binary_exponentiation(a, x, p);

    cout << "Результат (Ферма): " << result_fermat << endl;
    cout << "Результат (Бинарный): " << result_binary << endl;

    if (result_fermat != result_binary) {
        cerr << "Ошибка: Алгоритмы дали разные результаты!\n";
        
    } else {
        cout << "Результаты совпадают!\n";
    }

}