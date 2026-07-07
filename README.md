# Pi_approximate_Monte_Carlo_Method

Approximate Pi using Monte Carlo Method, inspired by https://en.wikipedia.org/wiki/Monte_Carlo_method

What the heck is std::atomic<T> ?

As I am learning c++, i wanted to find out and this is the result.

My learning topics are:

std::atomic<T>

Concurrency

Program with feedback to the user program it still running

Validating user input

Splitting source code into appropriate files

Measuring execution time

Raw pointers and apprporiate clean up

Valgrind to check memory leaks

Try-catch blocks

Focus on learning, not performance

Compile: g++ main.cpp get_valid_input.cpp pi_approx.cpp -g -o Pi_approx_cli

Valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-limit=no --log-file=valgrind_report.log --track-origins=yes ./Pi_approx_cli
