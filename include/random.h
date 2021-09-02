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
  RandomMatrix();
  Matrix sample(std::size_t n);
  void set_mean(Vec mean);
  void set_covariance(Matrix covariance);
private:
  Vec m_mean;
  Matrix m_covariance;
  Matrix m_transformed;
  RandomGenerator rng;
  Distribution dist;
};

#endif
