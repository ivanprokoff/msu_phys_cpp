#include <iostream>


int main() {
    int size;
    std::cout << "Type in number of symbols: ";
    std::cin >> size;
    std::cin.ignore();

    char *str = new char[size + 1];

    std::cout << "Type in string: ";
    std::cin.getline(str, size + 1);

    int length = std::strlen(str);
    for (int i = 0; i < length / 2; ++i) {
        std::swap(str[i], str[length - i - 1]);
    }

    std::cout << "Inverted string: " << str << std::endl;
    delete[] str;

    return 0;
}

