#include "Integer.h"

Integer::Integer() : length(LIMIT)
{
    array = new int [length];
}

Integer::~Integer()
{
    length = 0;
    delete [] array;
}

Integer::Integer(int arr[])
{
    int size = sizeof(arr) / sizeof(arr[0]);
    length = size + 1;
    array = new int [length];
    for(int i = 0; i <= size; i++)
        array[i] = arr[i];
}


Integer Integer::operator = (const Integer &obj)
{
    Integer temp;
    for(int i = 0; i < obj.length; i++)
    {
        array[i] = obj.array[i];
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
    if(length != obj.length)
        return false;
    else {
        for(int i = 0; i < obj.length; i++) {
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
    for(int i = 0; i < obj.length; i++) {
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
    if (count > LIMIT - obj.length) {
        cout << "Limit of the array is 20000 numbers." << endl;
        exit(1);
    }

    int *temp = new int [obj.length + count];



    for (int i = 0; i < count; i++) {
        cout << "Input your " << i + 1 << " number: ";
        input >> number;
        obj.array[i] = number;
    }
    cout << "That's all." << endl;

    return input;
}
