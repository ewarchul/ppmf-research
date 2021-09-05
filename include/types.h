#ifndef TYPES_H
#define TYPES_H

#include <functional>
#include <vector>
#include <blaze/Math.h>

using Vec = blaze::DynamicVector<double, blaze::columnVector>;
using Matrix = blaze::DynamicMatrix<double, blaze::columnMajor>;
using Population = Matrix;
using Eval = std::function<double(const double *xarg, std::size_t dim)>;

#endif
