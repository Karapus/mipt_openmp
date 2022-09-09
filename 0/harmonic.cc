#include <cassert>
#include <iostream>

int main(int argc, char *argv[]) {
  assert((argc == 2) && "argv[1] is the number of elements to sum");
  auto n = std::stoull(argv[1]);

  auto sum = 0.0;
  [[ omp::directive(parallel for reduction(+:sum)) ]]
    for (decltype(n) x = 1; x <= n; ++x)
      sum += 1.0 / x;

  std::cout << sum << std::endl;
}
