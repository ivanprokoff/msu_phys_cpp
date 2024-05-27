#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

class Vector {
public:
    Vector(float x, float y): x(x), y(y) {}
    Vector(): x(0), y(0) {}

    Vector& random_walk(float distance) {
        float angle = (static_cast<float>(rand()) / RAND_MAX) * 2 * M_PI;
        x += distance * cos(angle);
        y += distance * sin(angle);
        return *this;
    }

    float distance_to_origin() const {
        return std::sqrt(x * x + y * y);
    }

private:
    float x, y;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int N = 1000;
    const float target_distance = 50.0f;
    std::vector<int> steps_to_reach(N);

    for (int i = 0; i < N; ++i) {
        Vector position;
        int steps = 0;
        while (position.distance_to_origin() < target_distance) {
            position.random_walk(1.0f);
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
    for (int steps : steps_to_reach) {
        variance += std::pow(steps - mean_steps, 2);
    }
    float standard_deviation = std::sqrt(variance / N);

    std::cout << "Среднее число шагов: " << mean_steps << std::endl;
    std::cout << "Стандартное отклонение: " << standard_deviation << std::endl;

    return 0;
}
