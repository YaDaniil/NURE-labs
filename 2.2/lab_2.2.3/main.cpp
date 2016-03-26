#include <iostream>
#include "Integer.h"
using namespace std;

int main()
{
    int arr1[] = {10, 20, 144};
    int arr2[] = {1, 2, 6};
    Integer integer1(arr1);
    Integer integer2(arr2);

    cout << "Demonstration of ostream(<<) overloading: " << endl;
    cout << "integer1: ";
    cout << integer1;
    cout << "integer2: ";
    cout << integer2 << endl;

    cout << "Demonstration of \'==\' operator overloading: " << endl;
    cout << "integer1 == integer2 : ";
    cout << (integer1 == integer2) << endl;
    cout << "Demonstration of \'!=\' operator overloading: " << endl;
    cout << "integer1 != integer2 : ";
    cout << (integer1 != integer2) << endl;

    cout << "Demonstration of \'[]\' operator overloading: " << endl;
    cout << "integer1[2] : ";
    cout << integer1[2] << endl;

    cout << "Demonstration of istream(>>) overloading: " << endl;
    cin >> integer1;

    cout << "integer1 now consists :";
    cout << integer1;

    cin.get();
    return 0;
}




