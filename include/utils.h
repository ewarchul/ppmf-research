#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <ostream>
#include <spdlog/spdlog.h>
#include <type_traits>

#include "types.h"

class Solutions;
class Parameters;

namespace utils {
template <int Exponent, typename T>
auto pow_n_plus(const T &lhs, const T &rhs) -> decltype(lhs + rhs) {
  return std::pow(lhs + rhs, Exponent);
}
inline double get_default_lower_bound() { return -100; }
inline double get_default_upper_bound() { return 100; }

template <typename Printable_T> void print(const Printable_T &t) {
  if constexpr (std::is_same<Printable_T, Solutions>::value) {
    print_solutions(t);
  } else if constexpr (std::is_same<Printable_T, Parameters>::value) {
    print_parameters(t);
  } else {
    std::runtime_error("Unknown type");
  }
}
namespace evalfuncs {
template <size_t N, typename T> constexpr T F_sphere(const T *x) {
  T val = 0.0;
  for (size_t i = 0; i < N; ++i)
    val += x[i] * x[i];
  return val;
};
} // namespace evalfuncs

} // namespace utils

namespace blaze {
namespace internal {

template <typename TM, bool SO = blaze::columnMajor, typename VectorFunc>
blaze::DynamicVector<TM> apply(const blaze::DynamicMatrix<TM, SO> &dm,
                               VectorFunc op) {
  size_t ncol = dm.columns();
  size_t nrow = dm.rows();
  blaze::DynamicVector<TM> ret(ncol);
  for (size_t i = 0; i < ncol; ++i) {
    ret[i] = op(blaze::column(dm, i).data(), nrow);
  }
  return ret;
}
} // namespace internal
} // namespace blaze

#endif
