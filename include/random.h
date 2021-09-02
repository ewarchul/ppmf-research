#ifndef RANDOM_H
#define RANDOM_H

#include "types.h"
#include <blaze/Blaze.h>
#include <cstddef>

namespace random_utils {
template <typename RandomGenerator, typename Distribution>
auto random_vec(std::size_t size, RandomGenerator &rand, Distribution &dist)
    -> decltype(dist(rand)) {
  return blaze::generate(size, [&rand, &dist](size_t) { return dist(rand); });
}

template <typename RandomGenerator, typename Distribution>
auto random_matrix(std::size_t nrow, std::size_t ncol, RandomGenerator &rand,
                   Distribution &dist) -> decltype(dist(rand)) {
  return blaze::generate(nrow, ncol,
                         [&rand, &dist](size_t, size_t) { return dist(rand); });
}

}; // namespace random_utils

#endif
