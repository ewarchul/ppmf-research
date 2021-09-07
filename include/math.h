#ifndef MATH_H
#define MATH_H

#include <blaze/Math.h>
#include "types.h"

namespace blaze {
namespace internal {

template <typename TM, bool SO = blaze::columnMajor, typename VectorFunc>
blaze::DynamicVector<TM> apply(const blaze::DynamicMatrix<TM, SO> &dm,
                               VectorFunc op) {
  static_assert(types::is_valid_function<VectorFunc>::value,
                "Given operation is not a function.");
  size_t ncol = dm.columns();
  size_t nrow = dm.rows();
  blaze::DynamicVector<TM> ret(ncol);
  for (size_t i = 0; i < ncol; ++i) {
    ret[i] = op(blaze::column(dm, i).data(), nrow);
  }
  return ret;
};

template <typename Vector_T> Vector_T sort_ind(const Vector_T &vec) {
  static_assert(types::is_iterable<Vector_T>::value,
                "Given input is not iterable collection.");
  Vector_T indcs(vec.size());
  std::iota(indcs.begin(), indcs.end(), 0);
  std::sort(indcs.begin(), indcs.end(),
            [&](int i, int j) { return vec[i] < vec[j]; });
  return indcs;
};

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

#endif
