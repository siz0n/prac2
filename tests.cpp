#include <iostream>

using namespace std;

enum struct SmthType {
    CHECK = 1,
    FIND,
    ISEXIST
};

int main() {
    int userCode;
    cin >> userCode;
    auto userType = static_cast<SmthType>(userCode);
    
    switch (userType) {
        case SmthType::CHECK:
            cout << " check";
            break;
        case SmthType::FIND:
            cout << "fint";
            break;
        case SmthType::ISEXIST:
           cout << "isexist";
            break;
        default:
            cout << "..." << endl;
    }

    return 0;
}