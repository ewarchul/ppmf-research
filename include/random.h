#ifndef RANDOM_H
#define RANDOM_H



#include <blaze/Blaze.h>
#include <cstddef>
#include <random>

#include "types.h"
#include "math.h"

template <typename RandomGenerator = std::mt19937,
          typename Distribution = std::normal_distribution<double>>
class RandomMatrixGenerator {
public:
  RandomMatrixGenerator() {}
  RandomMatrixGenerator(const uint64_t &seed) : m_seed(seed) {}
  RandomMatrixGenerator(const Vec &mean, const Matrix &cov, const uint64_t &seed)
      : m_mean(mean), m_seed(seed) {
    m_rng.seed(m_seed);
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
  uint64_t m_seed = 5;
  size_t m_dim;
};

#endif
