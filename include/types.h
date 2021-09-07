#ifndef TYPES_H
#define TYPES_H

#include <blaze/Math.h>
#include <functional>
#include <vector>
#include <type_traits>

using Vec = blaze::DynamicVector<double, blaze::columnVector>;
using Matrix = blaze::DynamicMatrix<double, blaze::columnMajor>;
using Population = Matrix;
using Eval = std::function<double(const double *xarg, std::size_t dim)>;

namespace types {
template <typename T, typename = void> struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end())>>
    : std::true_type {};

template <typename T>
struct is_valid_function
    : std::integral_constant<bool, std::is_function_v<T> ||
                                       std::is_same_v<T, Eval>> {};
} // namespace types

#endif
