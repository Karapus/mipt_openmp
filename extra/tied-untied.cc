#include <iostream>
#include <omp.h>

#ifdef NOUNTIED
#define UNTIED
#else
#define UNTIED untied
#endif

bool flag;
[[omp::directive(threadprivate(flag))]]

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  auto NTasks = 10;
  if (argc == 2) NTasks = std::stoi(argv[1]);

  auto NErrs = 0;
  [[omp::directive(parallel num_threads(2))]] {
    for (decltype(NTasks) iTask{}; iTask < NTasks; ++iTask)
      [[omp::directive(task UNTIED)]] {
        flag = true;
        [[omp::directive(taskyield)]];
        if (!flag) ++NErrs;
        flag = false;
      }
  }
  std::cout << "Error rate: " << double(NErrs) / NTasks << std::endl;
}
