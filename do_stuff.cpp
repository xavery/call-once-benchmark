#include <benchmark/benchmark.h>

extern "C" void actually_do_stuff(void) {
  benchmark::DoNotOptimize(printf(""));
  benchmark::ClobberMemory();
}
