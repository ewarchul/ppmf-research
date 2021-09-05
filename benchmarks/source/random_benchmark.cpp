#include "../../include/random.h"
#include "../../reference/rmatrix.h"
#include <benchmark/benchmark.h>
#include <blaze/Math.h>
#include <iostream>

static void RandomMatrix_SCtor(benchmark::State &state) {
  uint64_t seed = 10;
  for (auto _ : state) {
    RandomMatrix random(seed);
  }
}

static void RandomMatrix_Ctor(benchmark::State &state) {
  uint64_t seed = 10;
  auto rng = std::mt19937(seed);
  auto dist = std::uniform_real_distribution{};
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    Vec mean(dim, 1); 
    blaze::IdentityMatrix<double, blaze::rowMajor> covariance(dim);
    auto cov_mat = blaze::declid(covariance);
    state.ResumeTiming();
    RandomMatrix random(mean, cov_mat, seed);
  }
}

static void RandomMatrix_Sampling(benchmark::State &state) {
  uint64_t seed = 10;
  auto rng = std::mt19937(seed);
  auto dist = std::uniform_real_distribution{};
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    int lambda = 4 * std::floor(3 * std::log(dim));
    Vec mean(dim, 1); 
    blaze::IdentityMatrix<double, blaze::rowMajor> covariance(dim);
    auto cov_mat = blaze::declid(covariance);
    RandomMatrix random(mean, cov_mat, seed);
    state.ResumeTiming();
    random.sample(lambda);
  }
}

static void Eigen_SCtor(benchmark::State &state) {
  for (auto _ : state) {
    Eigen::EigenMultivariateNormal<double> random;
  }
}

static void Eigen_Ctor(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    dVec mean = dVec::Constant(dim, 1);
    dMat cov_mat = dMat::Identity(dim, dim);
    state.ResumeTiming();
    Eigen::EigenMultivariateNormal<double> random(mean, cov_mat);
  }
}

static void Eigen_Sample(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    int lambda = 4 * std::floor(3 * std::log(dim));
    dVec mean = dVec::Constant(dim, 1);
    dMat cov_mat = dMat::Identity(dim, dim);
    Eigen::EigenMultivariateNormal<double> random(mean, cov_mat);
    state.ResumeTiming();
    random.samples(lambda, 1);
  }
}

static void Eigen_CtorCholesky(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    dVec mean = dVec::Constant(dim, 1);
    dMat cov_mat = dMat::Identity(dim, dim);
    state.ResumeTiming();
    Eigen::EigenMultivariateNormal<double> random(mean, cov_mat, true);
  }
}

static void Eigen_SampleCholesky(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    int dim = state.range(0);
    int lambda = 4 * std::floor(3 * std::log(dim));
    dVec mean = dVec::Constant(dim, 1);
    dMat cov_mat = dMat::Identity(dim, dim);
    Eigen::EigenMultivariateNormal<double> random(mean, cov_mat, true);
    state.ResumeTiming();
    random.samples(lambda, 1);
  }
}


BENCHMARK(RandomMatrix_SCtor);
BENCHMARK(Eigen_SCtor);


/* Low scale */

BENCHMARK(Eigen_Ctor)->DenseRange(10, 100, 10);
BENCHMARK(Eigen_CtorCholesky)->DenseRange(10, 100, 10);

BENCHMARK(Eigen_Sample)->DenseRange(10, 100, 10);
BENCHMARK(Eigen_SampleCholesky)->DenseRange(10, 100, 10);

BENCHMARK(RandomMatrix_Ctor)->DenseRange(10, 100, 10);
BENCHMARK(RandomMatrix_Sampling)->DenseRange(10, 100, 10);

//[> Large scale  <]

BENCHMARK(Eigen_Ctor)->DenseRange(200, 1000, 100);
BENCHMARK(Eigen_CtorCholesky)->DenseRange(200, 1000, 100);

BENCHMARK(Eigen_Sample)->DenseRange(200, 1000, 100);
BENCHMARK(Eigen_SampleCholesky)->DenseRange(200, 1000, 100);

BENCHMARK(RandomMatrix_Ctor)->DenseRange(200, 1000, 100);
BENCHMARK(RandomMatrix_Sampling)->DenseRange(200, 1000, 100);

