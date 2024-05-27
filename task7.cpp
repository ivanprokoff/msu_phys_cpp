#include <iostream>
#include <fstream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    int size;

public:
    DynamicArray() : data(nullptr), size(0) {}

    DynamicArray(const DynamicArray& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) {
            std::cerr << "Index out of bounds\n";
            return;
        }

        int* newData = new int[size + 1];
        std::copy(data, data + index, newData);
        newData[index] = value;
        std::copy(data + index, data + size, newData + index + 1);
        delete[] data;
        data = newData;
        ++size;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Перегрузка оператора вывода для печати массива
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i] << ' ';
        }
        return os;
    }
};

int main() {
    int numberOfElements, index, value;
    std::cout << "Enter the number of elements: ";
    std::cin >> numberOfElements;

    DynamicArray array;

    for (int i = 0; i < numberOfElements; ++i) {
        array.insert(i, 0);
    }

    std::cout << "Enter index and value to insert: ";
    std::cin >> index >> value;

    array.insert(index, value);

    std::cout << "Array after insertion: " << array << std::endl;

    if (numberOfElements > 0) {
        array[0] = 999;
    }

    std::cout << "Array after changing first element: " << array << std::endl;

    std::ofstream file("output.txt");
    if (file.is_open()) {
        file << array;
        file.close();
    } else {
        std::cerr << "Unable to open file\n";
    }

    return 0;
}
