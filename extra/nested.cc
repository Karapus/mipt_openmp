#include <iostream>
#include <omp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  omp_set_max_active_levels(3);
  auto tid0 = omp_get_thread_num();
  auto nt0 = omp_get_num_threads();
  [[omp::directive(parallel)]] {
    auto tid1 = omp_get_thread_num();
    auto nt1 = omp_get_num_threads();
    [[omp::directive(parallel)]] {
      auto tid2 = omp_get_thread_num();
      auto nt2 = omp_get_num_threads();
      [[omp::directive(parallel)]] {
        auto tid3 = omp_get_thread_num();
        auto nt3 = omp_get_num_threads();
        [[omp::directive(critical)]] std::cout
          << " tid0 #" << tid0 << " nt0 #" << nt0
          << " tid1 #" << tid1 << " nt1 #" << nt1
          << " tid2 #" << tid2 << " nt2 #" << nt2
          << " tid3 #" << tid3 << " nt3 #" << nt3
          << std::endl;
      }
    }
  }
}
