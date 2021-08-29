#ifndef UTILS_H
#define UTILS_H

#include <cmath>

namespace utils {
template <typename T, int Exp> struct pow_n_plus {
  constexpr T operator()(const T &lhs, const T &rhs) const {
    return std::pow(lhs + rhs, Exp);
  }
};
inline double get_default_lower_bound() { return -100; }
inline double get_default_upper_bound() { return 100; }

} // namespace utils

#endif
