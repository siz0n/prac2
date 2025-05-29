#include <iostream>
#include <tuple> 
#include "math.h"
using namespace std;



void extendedEuclid() {
    int a, b;
    cout << "Введите число c: ";
    cin >> a;
    cout << "Введите число m: ";
    cin >> b;

    auto result = Euclid(a, b); // Кортеж (d, u, v)


    cout << "u = " << get<1>(result) << ", v = " << get<2>(result) << endl;
    cout << "Проверка: " << a << " * " << get<1>(result) << " + " << b << " * " << get<2>(result)
         << " = " << a * get<1>(result) + b * get<2>(result) << endl;

    
}