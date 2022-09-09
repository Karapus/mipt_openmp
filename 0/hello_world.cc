#include <iostream>
#include <omp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  [[omp::directive(parallel)]] {
    [[omp::directive(critical)]] std::cout
        << "Thread #" << omp_get_thread_num() << " out of "
        << omp_get_num_threads() << std::endl;
  }
}
