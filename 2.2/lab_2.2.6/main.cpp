#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void quickSort(int b, int e, int* array)
{
    int l = b, r = e;
    int mid = array[(l + r) / 2];
    while (l <= r) {
        while (array[l] < mid)
            l++;
        while (array[r] > mid)
            r--;
        if (l <= r)
            swap(array[l++], array[r--]);
    }
    if (b < r)
        quickSort(b, r, array);
    if (e > l)
        quickSort(l, e, array);
}

long fullyWithoutSTL()
{

    unsigned clock = 0;

    __asm rdtsc;
    __asm mov[clock], eax;


    const int length = 10000;
    //int array[length];
    int * array = new int[length];
    int countOfOdds = 0;
    int evenArrayLength;

    // Randomizing array
    for (int i = 0; i < length; i++)
        array[i] = rand() % 1000;

    // Place zero in every fifth element
    for (int i = 4; i < length; i += 5)
        array[i] = 0;


    // Deleting all odd digits by shifting all right rest on 1 to left
    // and then creating smaller array that contains only evens

    //Shifting
    for (int i = 0; i < length; i++) {
        if ((array[i] & 1)) {
            for (int j = i; j < length; j++) {
                array[j] = array[j + 1];
            }
            countOfOdds++;
        }
    }

    //Calculate length of new array and create it
    evenArrayLength = length - countOfOdds;
    int *evenArray = new int[evenArrayLength];
    //int evenArray[evenArrayLength];

    //Fill new array with even digits
    for (int i = 0; i < evenArrayLength; i++)
        evenArray[i] = array[i];

    // Perform quick sort
    quickSort(0, evenArrayLength - 1, evenArray);

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    return clock;

}

long withContainers()
{

    unsigned clock = 0;

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    int length = 10000;

    vector<int> initialVector;

    // Randomize vector
    for (int i = 0; i < length; i++)
        initialVector.push_back(rand() % 1000);

    // Place zero in every fifth element
    for (int i = 4; i < length; i += 5)
        initialVector[i] = 0;


    // Deleting all odd digits
    for (int i = 0; i < initialVector.size(); i++) {
        if ((initialVector.at(i) & 1)) {
            initialVector.erase(initialVector.begin() + i);
        }
    }

    // Convert vector to array
    int *array = new int[initialVector.size()];
    //int array[initialVector.size()];
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

bool isOdd(int i) { return ((i % 2) == 1); }

// WTF
int zeroEveryFifth(vector<int> vec) {
    for (int i = 4; i < vec.size(); i += 5) {
        vec.at(i) == 0;
        //return vec.at(i);
    }
    return 0;
}

long fullSTL()
{

    unsigned clock = 0;

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;
    int length = 10000;

    vector<int> vector;
    std::vector<int>::iterator iter1, new_end;

    // Randomize vector
    for (int i = 0; i < length; i++)
        vector.push_back(rand() % 1000);

    // Place zero in every fifth element
    //transform(vector.begin(), vector.end(), vector.begin(), zeroEveryFifth(vector));
    for (int i = 4; i < length; i += 5)
        vector[i] = 0;


    // Deleting all odd digits
    new_end = remove_if(vector.begin(), vector.end(), isOdd);
    // Trim unnecessary stuff
    vector.erase(new_end, vector.end());

    // Perform quick sort
    sort(vector.begin(), vector.end());

    __asm rdtsc;
    __asm sub eax, [clock];
    __asm mov[clock], eax;

    return clock;

}



int main()
{
    srand((unsigned)time(NULL));

    cout << "Time for processing without STL: " << fullyWithoutSTL() << endl;
    cout << "Time for processing only with containers: " << withContainers() << endl;
    cout << "Time for processing with STL: " << fullSTL() << endl;


    getchar();
    return 0;
}