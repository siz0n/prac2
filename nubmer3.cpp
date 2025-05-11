#include <iostream>
#include <tuple> 
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

int main() {
    int c, m;
    cout << "Введите число c: ";
    cin >> c;
    cout << "Введите модуль m: ";
    cin >> m;

    auto [d, u, v] = eEuclid(c, m); 

    if (d != 1) {
        cerr << "Обратного элемента не существует (НОД ≠ 1)" << endl;
        return 1;
    }

    // нужно положительно
    int inverse= (u % m + m) % m;

    cout << "Обратный элемент d = " << inverse << endl;
    cout << c << "^-1" << " " << " * " << " mod " << m 
         << " = " << inverse<< endl;

    return 0;
}