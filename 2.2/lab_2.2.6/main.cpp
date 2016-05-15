#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void quickSort(int b, int e, int* array)
{
    int l = b, r = e;
    int mid = array[(l + r) / 2];
    while (l <= r)
    {
        while (array[l] < mid)
            l++;
        while (array[r] > mid)
            r--;
        if (l <= r)
            swap (array[l++], array[r--]);
    }
    if (b < r)
        quickSort(b, r, array);
    if (e > l)
        quickSort(l, e, array);
}

long fullyWithoutSTL() {

    unsigned clock = 0;

    __asm rdtsc;
    __asm mov[clock], eax;


    int length = 10000;
    int array[length];
    int countOfOdds = 0;
    int evenArrayLength;

    // Randomizing array
    for(int i = 0; i < length; i++)
        array[i] = rand() % 1000;

    // Place zero in every fifth element
    for(int i = 4; i < length; i+= 5)
        array[i] = 0;


    // Deleting all odd digits by shifting all right rest on 1 to left
    // and then creating smaller array that contains only evens

    //Shifting
    for(int i = 0; i < length; i++) {
        if((array[i] & 1)) {
            for(int j = i; j < length; j++) {
                array[j] = array[j + 1];
            }
            countOfOdds++;
        }
    }

    //Calculate length of new array and create it
    evenArrayLength = length - countOfOdds;
    int evenArray[evenArrayLength];

    //Fill new array with even digits
    for(int i = 0; i < evenArrayLength; i++)
        evenArray[i] = array[i];

    // Perform quick sort
    quickSort(0, evenArrayLength - 1, evenArray);

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    return clock;

}

long withContainers() {

    unsigned clock = 0;

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    int length = 10000;

    vector<int> initialVector;

    // Randomize vector
    for(int i = 0; i < length; i++)
        initialVector.push_back(rand() % 1000);

    // Place zero in every fifth element
    for(int i = 4; i < length; i+= 5)
        initialVector[i] = 0;


    // Deleting all odd digits
    for(int i = 0; i < length; i++) {
        if((initialVector[i] & 1)) {
            initialVector.erase(initialVector.begin() + 1);
        }
    }

    // Convert vector to array
    int array[initialVector.size()];
    copy(initialVector.begin(), initialVector.end(), array);
    // Perform quick sort
    quickSort(0, initialVector.size() - 1, array);
    // Convert back to vector
    vector<int> newVector(array, array + sizeof array / sizeof array[0]);

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    return clock;
}

bool isOdd (int i) { return ((i%2) == 1); }

long fullSTL() {

    unsigned clock = 0;

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;
    int length = 10000;

    vector<int> vector;
    //vector<int>::iterator iter1, new_end;

    // Randomize vector
    for(int i = 0; i < length; i++)
        vector.push_back(rand() % 1000);

    // Place zero in every fifth element
    //transform(vector.begin(), vector.end(), vector.begin(), zeroEveryFifth(vector));
    for(int i = 4; i < length; i+= 5)
        vector[i] = 0;


    // Deleting all odd digits
    /*
    for(iter1 = vector.begin(); iter1 != vector.end(); iter1++)
        cout<<*iter1<<" ";
    cout<<endl;

    new_end = remove_if(vector.begin(), vector.end(), isOdd);

    for(iter1 = vector.begin(); iter1 != vector.end(); iter1++)
        cout<<*iter1<<" ";
    cout<<endl;

    vector.erase(new_end, vector.end());

    for(iter1 = vector.begin(); iter1 != vector.end(); iter1++)
        cout<<*iter1<<" ";
    cout<<endl;
*/
    for(int i = 0; i < length; i++) {
        if((vector[i] & 1)) {
            vector.erase(vector.begin() + 1);
        }
    }

    // Perform quick sort
    sort(vector.begin(), vector.end(), std::greater<int>());

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    return clock;

}



int main() {
    srand((unsigned)time(NULL));

    cout << fullyWithoutSTL() << endl;
    cout << withContainers() << endl;
    cout <<  fullSTL() << endl;


    getchar();
    return 0;
}