#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <ostream>
#include <spdlog/spdlog.h>
#include <type_traits>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>

class Solutions;
class Parameters;

namespace utils {
  template <int Exponent, typename T>
  auto pow_n_plus(const T &lhs, const T &rhs) -> decltype(lhs + rhs) {
    return std::pow(lhs + rhs, Exponent);
  }
  inline double get_default_lower_bound() { return -100; }
  inline double get_default_upper_bound() { return 100; }

  template <typename Printable_T>
  void print(const Printable_T &t) {
    if constexpr (std::is_same<Printable_T, Solutions>::value) {
      print_solutions(t);
    } else if constexpr (std::is_same<Printable_T, Parameters>::value) {
      print_parameters(t);
    } else {
      std::runtime_error("Unknown type");
    }
  }
} // namespace utils

#endif
