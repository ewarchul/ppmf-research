#ifndef CMAES_H
#define CMAES_H

#include <eigen3/Eigen/Eigen>
#include <functional>
#include <vector>

#include "cma.h"
#include "sigma_adaptation.h"

#include "parameters.h"
#include "solutions.h"
#include "types.h"

Eval sphere = [](const double *x, const int N) {
  double ret = 0.0;
  for (auto i = 0; i < N; ++i) {
    ret += x[i] * x[i];
  }
  return ret;
};

template <typename T_CMAUpdate, typename T_SigmaUpdate> class cmaes {
public:
  cmaes(Eval evalfun, Parameters params)
      : m_evalfun(evalfun), m_parameters(params), m_evals(0), m_iter(0) {
    m_solutions = Solutions(params);
  };

  Solutions optimize() {
    while (!terminate()) {
      Population pop = ask();
      evaluate(pop);
      tell();
    }
    return get_solutions();
  }

private:
  Population ask() {
    auto dim = m_parameters.get_dim();
    return blaze::generate(dim, dim,
                           [](std::size_t i, std::size_t k) { return 2; });
  }
  void tell() {
    T_CMAUpdate::update(m_solutions);
    T_SigmaUpdate::update(m_solutions);
  }
  bool terminate() {
    return m_parameters.get_max_iter() > m_iter ? true : false;
  }
  void evaluate(Population &pop);
  void inc_iter() {
    m_iter++;
    m_solutions.set_iter(m_iter);
  }
  void inc_evals(const int evals) {
    m_evals += evals;
    m_solutions.set_evals(evals);
  }

  Solutions &get_solutions() { return m_solutions; }

  unsigned int m_evals;
  unsigned int m_iter;
  Eval m_evalfun;
  Parameters m_parameters;
  Solutions m_solutions;
};

#endif
