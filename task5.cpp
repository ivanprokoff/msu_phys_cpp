#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

class Vector {
public:
    // Переопределяемый метод для вычисления модуля вектора
    virtual float modulus() const = 0;

    // Деструктор
    virtual ~Vector() {}

    virtual Vector& operator+=(const Vector& rhs) = 0;
    virtual Vector& operator-=(const Vector& rhs) = 0;
    virtual Vector& operator*=(float scalar) = 0;
    virtual Vector& operator/=(float scalar) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        v.print(os);
        return os;
    }

protected:
    virtual void print(std::ostream& os) const = 0;
};

class Vector3d : public Vector {
public:
    Vector3d(float x, float y, float z): x(x), y(y), z(z) {}
    Vector3d(): x(0), y(0), z(0) {}

    // Переопределенный метод для вычисления модуля вектора
    float modulus() const override {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3d& operator+=(const Vector& rhs) override {
        const Vector3d& v = static_cast<const Vector3d&>(rhs);
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3d& operator-=(const Vector& rhs) override {
        const Vector3d& v = static_cast<const Vector3d&>(rhs);
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3d& operator*=(float scalar) override {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3d& operator/=(float scalar) override {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

protected:
    void print(std::ostream& os) const override {
        os << "Vector3d(" << x << ", " << y << ", " << z << ")";
    }

private:
    float x, y, z;
};

Vector3d random_step_3d(float step_size) {
    float azimuth = (static_cast<float>(rand()) / RAND_MAX) * 2 * M_PI;
    float polar = (static_cast<float>(rand()) / RAND_MAX) * M_PI;
    float x = step_size * sin(polar) * cos(azimuth);
    float y = step_size * sin(polar) * sin(azimuth);
    float z = step_size * cos(polar);
    return Vector3d(x, y, z);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int N = 30;
    const float target_radius = 50.0f;
    std::vector<int> steps_to_reach(N);
    float step_size = 1.0f;

    for (int i = 0; i < N; ++i) {
        Vector3d position;
        int steps = 0;
        while (position.modulus() < target_radius) {
            Vector3d step = random_step_3d(step_size);
            position += step;
            steps++;
        }
        steps_to_reach[i] = steps;
    }

    float mean_steps = 0;
    for (int steps : steps_to_reach) {
        mean_steps += steps;
    }
    mean_steps /= N;

    float variance = 0;
    for (auto steps : steps_to_reach) {
        variance += std::pow(steps - mean_steps, 2);
    }
    variance /= N;
    float standard_deviation = std::sqrt(variance);

    std::cout << "Среднее число шагов для достижения радиуса " << target_radius << " м: " << mean_steps << std::endl;
    std::cout << "Стандартное отклонение: " << standard_deviation << std::endl;

    return 0;
}
