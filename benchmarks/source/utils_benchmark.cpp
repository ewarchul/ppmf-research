#include "../../include/utils.h"
#include <benchmark/benchmark.h>

static void BlazeInternal_apply(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    blaze::DynamicMatrix<double, blaze::columnMajor> mat(dim, dim, 1);
    auto sphere_func = [](const double *x, size_t N) -> double {
      double val = 0.0;
      for (size_t i = 0; i < N; ++i) {
        val += x[i] * x[i];
      }
      return val;
    };
    state.ResumeTiming();
    blaze::internal::apply(mat, sphere_func);
  }
}



BENCHMARK(BlazeInternal_apply)->DenseRange(10, 100, 10);

BENCHMARK(BlazeInternal_apply)->DenseRange(200, 1000, 100);

BENCHMARK(BlazeInternal_apply)->Arg(5000);
