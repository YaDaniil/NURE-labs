#include <iostream>
#include <assert.h>
using namespace std;

enum Algorithms { SUBSTITUTION, POLYALPHABETIC, XOR };

class Helper
{
private:
    ostream& out;
    int algorithm;
    string key;
public:

    Helper(ostream &out, int algorithm, const string &key) : out(out), algorithm(algorithm), key(key) {}

    void setOut(ostream& out) {
        //swap(this->out, out);
        this->out.copyfmt(out);
        this->out.clear(out.rdstate());
        this->out.basic_ios<char>::rdbuf(out.rdbuf());
    }

    void substitution(string data) {
        for (int i = 0; i < data.size(); i++)
            out << key[data[i]];
    }

    void polyalphabeticSubstitution(string data) {
        string encrypted;

        for (int i = 0, j = 0; i < data.length(); ++i) {
            char c = data[i];

            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;

            encrypted += (c + key[j] - 2 * 'A') % 26 + 'A';
            j = (j + 1) % key.length();
        }
        //data.assign(encrypted);
        out << encrypted;
    }

    void xorEncryption(string data) {
        string encrypted;
        for (int i = 0; i < data.size(); i++)
            encrypted[i] = data[i] ^ key[i];
        out <<  encrypted;
    }

    void encrypt(string data) {
        switch (algorithm) {
            case SUBSTITUTION:
                substitution(data);
                break;

            case POLYALPHABETIC:
                polyalphabeticSubstitution(data);
                break;

            case XOR:
                xorEncryption(data);
                break;
            default:
                assert("WTF");
                break;
        }
    }

};

Helper encrypt(int algorithm, string key) {
    return Helper(cout, algorithm, key);
}

Helper& operator << (ostream& os, Helper obj) {
    obj.setOut(os);
    return obj;
}

Helper& operator << (Helper& obj, string data) {
    obj.encrypt(data);
    return obj;
}

int main() {
    cout << encrypt(SUBSTITUTION, "key") << "Hello";
    cout << encrypt(POLYALPHABETIC, "key") << "Hello";
    cout << encrypt(XOR, "key") << "Hello";

    getchar();
    return 0;
}