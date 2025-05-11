#include <iostream>
#include <tuple> 
#include "nubmer2.h"
using namespace std;


tuple<int, int, int> eEuclid(int a, int b) {
    tuple<int, int, int> X = {a, 1, 0 } ;
    tuple<int, int, int> Y = {b, 0, 1};

    while (get<0>(Y) != 0) {
        int q = get<0>(X) / get<0>(Y); 
        
        tuple<int, int, int> T = make_tuple(
            get<0>(X) % get<0>(Y),              
            get<1>(X) - q * get<1>(Y),            
            get<2>(X) - q * get<2>(Y)             
        );
        X = Y; 
        Y = T; 
    }

    return X; 
}

void extendedEuclidDemo() {
    int a, b;
    cout << "Введите число a: ";
    cin >> a;
    cout << "Введите число b: ";
    cin >> b;

    auto result = eEuclid(a, b); // Кортеж (d, u, v)

    cout << "\nНОД(" << a << ", " << b << ") = " << get<0>(result) << endl;
    cout << "u = " << get<1>(result) << ", v = " << get<2>(result) << endl;
    cout << "Проверка: " << a << " * " << get<1>(result) << " + " << b << " * " << get<2>(result)
         << " = " << a * get<1>(result) + b * get<2>(result) << endl;

    
}