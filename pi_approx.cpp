#include <iostream>
#include <chrono>
#include <random>
#include "pi_approx.h"

Pi_approx::Pi_approx() {}

Pi_approx::~Pi_approx() {}

bool Pi_approx::pi_approx(int iterations_per_thread, std::atomic<int>& inside_circle, std::atomic<int>& outside_circle)
{
    std::mt19937_64 *prng = nullptr;
    std::uniform_real_distribution<> *distribution = nullptr;
    double *x = nullptr; double *y = nullptr;
    try {
        prng = new std::mt19937_64;
        prng->seed(std::chrono::steady_clock::now().time_since_epoch().count());
        distribution = new std::uniform_real_distribution<>(0.0, 1.0);
        x = new double; y = new double;
    } catch (const std::exception& e) {
        std::cout << "A standard exception was caught, with message: '"
                  << e.what() << "'\n";
    }
    catch (...) {
        std::cout << "Some other exception was caught.\n";
    }
    for (std::size_t i=0; i<iterations_per_thread; i++){
        *x = (*distribution)(*prng);
        *y = (*distribution)(*prng);
        ((*x)*(*x)+(*y)*(*y) <= 1.) ? inside_circle++ : outside_circle++;
    }
    delete x;
    delete y;
    delete prng;
    delete distribution;
    x = nullptr;
    y = nullptr;
    prng = nullptr;
    distribution = nullptr;
    return true;
}
