#ifndef LAB_2_2_3_INTEGER_H
#define LAB_2_2_3_INTEGER_H

#include <iostream>
#include <vector>

using namespace std;

const int LIMIT = 20000;

class Integer {

private:

    vector<int> array;

public:

    Integer();

    Integer(int arr[]);

    Integer(vector<int> arr);

    Integer operator = (const Integer &obj);

    bool operator == (const Integer &obj) const;

    bool operator != (const Integer &obj) const;

    int& operator [] (int n);

    friend ostream& operator << (ostream &output, const Integer &obj);

    friend istream& operator >> (istream &input, Integer &obj);

};



#endif //LAB_2_2_3_INTEGER_H