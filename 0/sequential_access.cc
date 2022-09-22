#include <iostream>
#include <omp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int SharedVal = 0;
  [[omp::directive(parallel)]] {
    auto NThreads = omp_get_num_threads();
    [[omp::directive(for ordered)]]
      for (decltype(NThreads) i = 0; i < NThreads; ++i)
        [[omp::directive(critical)]] std::cout
          << "Thread #" << omp_get_thread_num()
          << ": SharedVal == " << SharedVal++
          << std::endl;
  }
}
