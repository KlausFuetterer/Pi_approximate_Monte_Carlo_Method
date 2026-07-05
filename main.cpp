#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <iomanip>
#include "pi_approx.h"
#include "get_valid_input.h"

int main(){
    std::cout << std::flush;
    std::cout << std::setprecision(9);
    std::system("clear");
    std::cout << "\nMain thread std::this_thread::get_id(): " << std::this_thread::get_id() << std::endl;
    int iterations, num_threads;
    std::atomic<int> inside_circle(0), outside_circle {0};
    do {
        iterations = get_valid_input("How many Iterantions (0 < int < INT_MAX) ?          ---> ");
    }
    while (iterations < 1);
    std::cout << "std::thread::hardware_concurrency():                ---> "
              << std::thread::hardware_concurrency() << std::endl;
    do {
        num_threads = get_valid_input("How many Threads for Calculations (0 < int <= 31) ? ---> ");
        if ((num_threads > iterations) && !(num_threads > 31)) std::cout << "Threads must be <= iterations." << std::endl;
    }
    while ((num_threads < 1)
           || (num_threads > 31)
           || (iterations < num_threads));
    std::chrono::time_point<std::chrono::steady_clock> calculations_start =
        std::chrono::steady_clock::now();
    int iterations_per_thread = iterations / num_threads;
    if (iterations_per_thread * num_threads != iterations)
        std::cout << "Iterations reduced to                               ---> "
                  << iterations_per_thread * num_threads << std::endl;
    std::vector<Pi_approx*> *instances_vec = nullptr;
    std::vector<std::future<bool>*> *future_vec = nullptr;
    bool *all_futures_ready = nullptr;
    try {
        instances_vec = new std::vector<Pi_approx*>;
        future_vec = new std::vector<std::future<bool>*>;
        for (std::size_t i=0; i<num_threads; i++){
            instances_vec->push_back(new Pi_approx);
            future_vec->push_back(new std::future<bool>
                                  (std::async(std::launch::async, &Pi_approx::pi_approx,
                                              instances_vec->at(i), std::ref(iterations_per_thread),
                                              std::ref(inside_circle), std::ref(outside_circle))));
        };
        all_futures_ready = new bool(false);
        while (!*all_futures_ready){
            *all_futures_ready = true;
            for (std::size_t i=0; i<future_vec->size(); i++){
                if (future_vec->at(i)->wait_for(std::chrono::microseconds(1)) != std::future_status::ready) {
                    *all_futures_ready = false;
                    break;
                }
            }
            std::cout << "\rinside_circle: " << inside_circle.load()
                      << ", outside_circle: " << outside_circle.load()
                      << " Pi approximation: " << 4.*(double)inside_circle/((double)iterations_per_thread*(double)num_threads)
                      << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Prevent CPU overuse
        }
    } catch (...) {
        std::cout << "An exception was caught.";
    }
    std::cout << "\rinside_circle: " << inside_circle.load()
              << ", outside_circle: " << outside_circle.load() << std::endl;
    for (std::size_t i=0; i<num_threads; i++){
        delete instances_vec->at(i);
        instances_vec->at(i) = nullptr;
        delete future_vec->at(i);
        future_vec->at(i) = nullptr;
    };
    delete instances_vec;
    instances_vec = nullptr;
    delete future_vec;
    future_vec = nullptr;
    delete all_futures_ready;
    all_futures_ready = nullptr;
    std::chrono::time_point<std::chrono::steady_clock> calculations_end =
        std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1, 1000000>> calculations_duration = calculations_end - calculations_start;
    std::cout << "main(): Calculations duration:               ---> "
              << calculations_duration.count() << " microseconds." << std::endl;
              std::cout << "main(): Calculations duration:               ---> ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(calculations_duration).count()
              << " s " << std::chrono::duration_cast<std::chrono::milliseconds>(calculations_duration).count() % 1000
              << " ms "
              << std::chrono::duration_cast<std::chrono::microseconds>(calculations_duration).count() % 1000 % 1000
              << " us." << std::endl;
    std::cout << "Pi=                                          ---> "
              << 4.*(double)inside_circle/((double)iterations_per_thread*(double)num_threads) << std::endl;
    std::cout << "main(): Program completed." << std::endl;
    return 0;
}
