#include "Integer.h"

Integer::Integer(){}

Integer::Integer(int arr[])
{
    int size = sizeof(arr) / sizeof(arr[0]);
    for(int i = 0; i <= size; i++) {
        array.push_back(arr[i]);
    }
}

Integer::Integer(vector<int> arr)
{
    for(int i = 0; i < arr.size(); i++) {
        array.push_back(arr[i]);
    }
}

Integer Integer::operator = (const Integer &obj)
{
    Integer temp;
    for(int i = 0; i < obj.array.size(); i++)
    {
        this->array.push_back(obj.array[i]);
    }
    return temp;
}

int& Integer::operator [] (int n)
{
    if(n < 0 || n >= LIMIT)
    {
        cout << "\nWrong index!";
        exit(1);
    }
    return array[n];
}

bool Integer::operator == (const Integer &obj) const
{
    if(array.size() < obj.array.size() ||
            array.size() > obj.array.size())
        return false;


    else {
        for(int i = 0; i < array.size(); i++) {
            if(array[i] != obj.array[i])
                return false;
        }
        return true;
    }
}

bool Integer::operator != (const Integer &obj) const
{
    return !(*this == obj);
}

ostream& operator << (ostream &output, const Integer &obj)
{
    for(int i = 0; i < obj.array.size(); i++) {
        output << obj.array[i] << " ";
    }
    output << endl;
    return output;
}

istream& operator >> (istream  &input, Integer &obj)
{
    int count, number;

    cout << "How much numbers you want to add to the array?: ";
    cin >> count;
    if (count > LIMIT - obj.array.size()) {
        cout << "Limit of the array is 20000 numbers." << endl;
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        cout << "Input your " << i + 1 << " number: ";
        input >> number;
        obj.array.push_back(number);
    }
    cout << "That's all." << endl;

    return input;
}
