#ifndef PI_APPROX_H
#define PI_APPROX_H

#include <atomic>

class Pi_approx
{
public:
    Pi_approx();
    ~Pi_approx();
    bool pi_approx(int iterations_per_thread, std::atomic<int>& inside_circle, std::atomic<int>& outside_circle);
};

#endif // PI_APPROX_H
