#include <iostream>
#include <clocale>

// Функция вывода строки с параметром по умолчанию
void printString(const char* str = "Привет!") {
    std::cout << str << std::endl;
}

// Перегруженная функция для вывода строки n раз
void printString(const char* str, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << str << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    printString();
    printString("ААЫЫБДЫБДА");
    printString("Здравствуй, мир!", 3);
    return 0;
}
