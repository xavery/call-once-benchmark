#include <benchmark/benchmark.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

extern "C" void actually_do_stuff(void);

static void BM_StaticBool(benchmark::State& state) {
  static bool is_first_call = true;
  for (auto _ : state) {
  if (is_first_call) {
    is_first_call = false;
    actually_do_stuff();
  } else {
    actually_do_stuff();
  }
  }
}
BENCHMARK(BM_StaticBool);

static void do_first_call();

static void (*fptr)(void) = do_first_call;

void do_first_call() {
  fptr = actually_do_stuff;
  actually_do_stuff();
}

static void BM_FuncPtr(benchmark::State& state) {
  for (auto _ : state) {
    fptr();
  }
}
BENCHMARK(BM_FuncPtr);

extern "C" void selfmod_bench(void);

static void BM_SelfMod(benchmark::State& state) {
  for (auto _ : state) {
    selfmod_bench();
  }
}
BENCHMARK(BM_SelfMod);

int main(int argc, char** argv) {
  mprotect(reinterpret_cast<void*>(selfmod_bench), 4096,
    PROT_READ | PROT_WRITE | PROT_EXEC);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  return 0;
}
