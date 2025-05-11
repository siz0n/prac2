#include <iostream>
#include "number1.h"
#include "number2.h"
#include "number3.h"
#include "number4.h"
#include "number5.h"
#include "number6.h"


using namespace std;

int main() {
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Демонстрация возведения в степень\n";
        cout << "2. Расширенный алгоритм Евклида\n";
        cout << "3. Расширенный алгоритм Евклида для обратного числа\n";
        cout << "4. Шифрование\n";
        cout << "5. Цепная дробь\n";
        cout << "6. Атака\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch(choice) {
            case 1:
            exponentiation();
                break;
            case 2:
            extendedEuclid();
                break;
           case 3:
            euclid();
                break;
            case 4:
            shifr();
                break;
            case 5:
            uravnenie();
                break;
            case 6:
            hacker();
                break;
            case 0:
                cout << "Выход из программы...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while(choice != 0);

    return 0;
}