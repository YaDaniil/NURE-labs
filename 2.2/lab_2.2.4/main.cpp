#include <iostream>


template <class T>

class Array
{
private:
    T *array;
    int length;

public:
    Array(int length) {
        if (length <= 0 || length > 20000)
            throw std::exception();
        this->length = length;
        array = new T[length];
    }

    ~Array() {
        delete [] array;
        length = 0;
    }

    T& operator [] (int i) {
        if (i < 0 || i > length)
            throw std::out_of_range("Out of range exception");
        return array[i];
    }


    T& operator = (Array &that) {
        if (&that == this)
            return *this;
        if (array)
            delete[] array;

        length = that.length;
        if (that.array) {
            array = new T [that.length];
            for(int i = 0; i < that.length; i++) {
                array[i] = that.array[i];
            }
        } else
            array = 0;
        return *this;
    }


    bool operator == (Array &that) {
        if(that.length != length) {
            return false;
        } else
            for (int i = 0; i < that.length; i++) {
                if(array[i] != that.array[i])
                    return false;
            }
        return true;
    }


    bool operator != (Array &that) {
        return !(*this == that);
    }

    void addInt(int n, int i) {
        this->array[i] = n;
    }
    void addChar(char n, int i) {
        this->array[i] = n;
    }


    template <typename TT> friend std::ostream& operator << (std::ostream &stream, Array<TT> &that);
    template <typename TT> friend std::istream& operator >> (std::istream &stream, Array<TT> &that);
};

template<class T> std::ostream& operator << (std::ostream &stream, Array<T> &obj) {
    for(int i = 0; i < obj.length; i++)
        stream << obj.array[i] << " ";
    return stream;
}

template<class T> std::istream &operator >> (std::istream &stream, Array<T> &obj)
{
    for(int i = 0; i < obj.length; i++)
        stream>>obj.array[i];
    return stream;
}

int main() {
    try {
        int length = 0;
        std::cout << "Enter size of the array: ";
        std::cin >> length;

        Array<int> ints(length);
        std::cout << std::endl << "Array of Integers" << std::endl;
        std::cout << "Enter elements of array:" << std::endl;
        for (int i = 0; i < length; i++) {
            int n;
            std::cin >> n;
            ints.addInt(n, i);
        }

        std::cout << "Array: ";
        std::cout << ints << std::endl;
        if (length > 1) {
            int i, j = 0;
            std::cout << "Сomparison of two elements:" << std::endl;
            std::cout << "Enter index of first element: ";
            std::cin >> i;
            std::cout << "Enter index of second element: ";
            std::cin >> j;
            if (ints[i] == ints[j])
                std::cout << "Elements are equal" << std::endl;
            else
                std::cout << "Elements are not equal" << std::endl;
        }

        Array<char> chars(length);
        std::cout << std::endl << "Array of Chars" << std::endl;
        std::cout << "Enter elements of array:" << std::endl;
        getchar();

        for (int i = 0; i < length; i++) {
            char c = std::cin.get();
            getchar();
            chars.addChar(c, i);
        }
        std::cout << "Array: ";
        std::cout << chars << std::endl;
        if (length > 1) {
            int i, j = 0;
            std::cout << "Сomparison of two elements:" << std::endl;
            std::cout << "Enter index of first element: "; std::cin >> i;
            std::cout << "Enter index of second element: "; std::cin >> j;
            if (chars[i] == chars[j])
                std::cout << "Elements are equal" << std::endl;
            else
                std::cout << "Elements are not equal" << std::endl;
        }
    }
    catch (std::bad_alloc) {
        std::cout << "Fail to allocate the requested storage space" << std::endl;
    }
    catch (std::out_of_range) {
        std::cout << "Out of range exception" << std::endl;
    }
    catch (std::exception e) {
        std::cout << "An another exception was occured: " << e.what() << std::endl;
    }

    getchar();
    return 0;
}
