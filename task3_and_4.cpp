#include <iostream>
#include <cmath>

class Vector {
public:
    Vector(float x, float y): x(x), y(y) {std::cout << "Объект создан (с двумя параметрами)" << std::endl;}

    Vector(float x): x(x), y(0) {std::cout << "Объект создан (с одним параметром)" << std::endl;}

    Vector(): x(1), y(0) {std::cout << "Объект создан (по умолчанию)" << std::endl;}

    ~Vector() {
        std::cout << "Вектор удален." << std::endl;
    }

    void set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    void show() const {
        std::cout << "Вектор(" << x << ", " << y << ")" << std::endl;
    }

    float modulus() const {
        return std::sqrt(x * x + y * y);
    }

    Vector add(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    // Метод для "растяжения" вектора в заданное число раз
    Vector scale(float factor) const {
        return Vector(x * factor, y * factor);
    }

    void swap(Vector& other) {
        std::swap(x, other.x);
        std::swap(y, other.y);
    }

    Vector operator-() const {
        return Vector(-x, -y);
    }

    friend Vector operator-(const Vector& v1, const Vector& v2);

private:
    float x, y;
};

Vector operator-(const Vector& v1, const Vector& v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

int main() {
    float x1, y1;

    // Запрос координат первого вектора у пользователя
    std::cout << "Введите координаты первого вектора (x y): ";
    std::cin >> x1 >> y1;
    Vector vector1(x1, y1);

    Vector vector2;
    Vector def(3);

    std::cout << "Первый вектор: ";
    vector1.show();
    std::cout << "Второй вектор: ";
    vector2.show();

    vector1.swap(vector2);

    // Вывод координат векторов на экран после обмена
    std::cout << "Координаты после обмена:" << std::endl;
    std::cout << "Первый вектор: ";
    vector1.show();
    std::cout << "Второй вектор: ";
    vector2.show();

    Vector scaledVector = vector1.scale(3);
    std::cout << "Первый вектор, увеличенный в три раза: ";
    scaledVector.show();

    Vector sumVector = vector1.add(vector2);
    std::cout << "Сумма векторов: ";
    sumVector.show();

    std::cout << "Модуль первого вектора: " << sumVector.modulus() << std::endl <<std::endl;

    std::cout << "----------Задача 4----------" << std::endl;

    Vector v1(4.0, 3.0);
    Vector v2(2.0, 1.0);

    // Демонстрация перегрузки бинарного оператора "-" с помощью дружественной функции
    Vector v3 = v1 - v2;
    v3.show();

    // Демонстрация перегрузки унарного оператора "-" как метода класса
    Vector v4 = -v1;
    v4.show();
    std::cout << std::endl;
    return 0;
}
