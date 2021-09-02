#ifndef TYPES_H
#define TYPES_H

#include <functional>
#include <vector>
#include <blaze/Math.h>

using Vec = blaze::DynamicVector<double>;
using Matrix = blaze::DynamicMatrix<double>;
using Eval = std::function<double(const double *xarg, const int dim)>;

#endif
