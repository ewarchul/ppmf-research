#ifndef RANDOM_H
#define RANDOM_H

#include "types.h"
#include <blaze/Blaze.h>
#include <cstddef>
#include <random>

namespace blaze {
namespace internal {
template <typename RandomGenerator, typename Distribution>
auto random_vec(std::size_t size, RandomGenerator &rand, Distribution &dist)
    -> decltype(auto) {
  return blaze::generate(size, [&rand, &dist](size_t) { return dist(rand); });
}

template <typename RandomGenerator, typename Distribution>
auto random_matrix(std::size_t nrow, std::size_t ncol, RandomGenerator &rand,
                   Distribution &dist) -> decltype(auto) {
  return blaze::generate(nrow, ncol,
                         [&rand, &dist](size_t, size_t) { return dist(rand); });
}
} // namespace internal
} // namespace blaze

template <typename RandomGenerator, typename Distribution> class RandomMatrix {
public:
  RandomMatrix() = delete;
  RandomMatrix(const uint64_t &seed) : m_rng_seed(seed) {}
  RandomMatrix(const Vec &mean, const Matrix &cov, const uint64_t &seed)
      : m_mean(mean), m_rng_seed(seed) {
    m_rng(m_rng_seed);
    set_covariance(cov);
  }
  Matrix sample(size_t lambda) {
    return m_L_Cholesky *
               blaze::internal::random_matrix(m_dim, lambda, m_rng, m_dist) +
           blaze::expand(m_mean, lambda);
  }
  void set_mean(const Vec &mean) { m_mean = mean; }
  void set_covariance(const Matrix &covariance) {
    m_covariance = covariance;
    m_dim = covariance.columns();
    blaze::llh(m_covariance, m_L_Cholesky);
  }
  const Matrix &get_LMatrix() const { return m_L_Cholesky; }

private:
  Vec m_mean;
  Matrix m_covariance;
  Matrix m_L_Cholesky;
  mutable RandomGenerator m_rng;
  mutable Distribution m_dist;
  uint64_t m_rng_seed = std::mt19937::default_seed;
  size_t m_dim;
};

#endif
