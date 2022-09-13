#include <iostream>
#include <omp.h>

#ifndef NOCOPYIN
#define CLAUSE copyin(counter)
#else
#define CLAUSE
#endif

namespace {

static int counter = 0;
[[omp::directive(threadprivate(counter))]]

void printValue(auto Value) {
  [[omp::directive(critical)]] std::cout
    << "Thread #" << omp_get_thread_num()
    << " Value = " << Value
    << std::endl;
}

} //end namespace

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  printValue(counter++);
  [[omp::directive(parallel CLAUSE)]] 
    printValue(counter++);
}
