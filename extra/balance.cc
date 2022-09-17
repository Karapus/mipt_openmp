#include <omp.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#ifndef SCHEDULE
#define SCHEDULE
#endif

int main(int argc, char *argv[]) {
  auto n = 65ull;
  if (argc == 2)
    n = std::stoull(argv[1]);

  [[ omp::directive(parallel for SCHEDULE) ]]
    for (decltype(n) i = 0; i < n; ++i) {
      usleep(std::rand() % 1000);
      [[omp::directive(critical)]] std::cout
        << "Iteration #"
        << std::setfill('0') << std::setw(2)
        << i
        << " Thread #" << omp_get_thread_num()
        << std::endl;
    }
}
