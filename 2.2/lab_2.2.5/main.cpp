#include <iostream>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}

enum Algorithms {SUBSTITUTION, MULTI_SUBSTITUTION, XOR};

class Helper
{
private:
    ostream& out;
    int algorithm;
    string key;
public:

    Helper(ostream &out, int algorithm, const string &key) : out(out), algorithm(algorithm), key(key) { }

    void setOut(ostream& out) {
        this->out = move(out);
    }

    Helper& operator << (ostream& os, Helper obj) {
        obj.setOut(os);
        return obj;
    }
};