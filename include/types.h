#ifndef TYPES_H
#define TYPES_H

#include <eigen3/Eigen/Eigen>
#include <functional>
#include <vector>

using FitnessFunction = std::function<double(std::vector<double>, const int)>;
using DummyPopulation = std::vector<Eigen::VectorXd>;

#endif
