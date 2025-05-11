#include <iostream>
#include <vector>
#include <tuple>
#include "number5.h"

using namespace std;

vector<long long> continuedFraction(long long p, long long q) {
    vector<long long> cf;
    while (q != 0) {
        long long a = p / q;
        cf.push_back(a);
        long long r = p % q;
        p = q;
        q = r;
    }
    return cf;
}

tuple<int, int, int> extendedEuclid(int a, int b) {
    tuple<int, int, int> X = {a, 1, 0};
    tuple<int, int, int> Y = {b, 0, 1};

    while (get<0>(Y) != 0) {
        int q = get<0>(X) / get<0>(Y);

        tuple<int, int, int> T = {
            get<0>(X) % get<0>(Y),
            get<1>(X) - q * get<1>(Y),
            get<2>(X) - q * get<2>(Y)
        };
        X = Y;
        Y = T;
    }
    return X;
}

void uravnenie() {
    // Пример с цепной дробью
    long long p;
    long long q;
    cin >> p;
    cout << "/" << endl;
    cin >> q;
    vector<long long> result = continuedFraction(p, q);
    cout << p << "/" << q << " в виде цепной дроби = [";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i + 1 < result.size()) cout << ", ";
    }
    cout << "]" << endl;

    // Решение уравнения 1256a + 847b = 119
    cout << "\nРешение уравнения 1256a + 847b = 119 в целых числах:" << endl;
    int a_coeff = 1256;
    int b_coeff = 847;
    int c = 119;

    auto [gcd, x0, y0] = extendedEuclid(a_coeff, b_coeff);

    if (c % gcd != 0) {
        cout << "Решений нет, так как НОД(" << a_coeff << ", " << b_coeff 
             << ") = " << gcd << " не делит " << c << endl;
    } else {
        int factor = c / gcd;
        int x_part = x0 * factor;
        int y_part = y0 * factor;

        cout << "Частное решение: a = " << x_part << ", b = " << y_part << endl;
        cout << "Общее решение:" << endl;
        cout << "a = " << x_part << " + " << (b_coeff / gcd) << " * k" << endl;
        cout << "b = " << y_part << " - " << (a_coeff / gcd) << " * k" << endl;
        cout << "где k — любое целое число." << endl;
    }

}