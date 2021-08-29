#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "types.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>

enum class TerminationCriteria { TolX };

class Parameters {
public:
  Parameters(); 
  Parameters(const int dim, const Vec &x0, const double sigma,
             const int lambda);
  Parameters(const Vec &x0, const double sigma, const int lambda);
  Parameters(const Vec &x0, const double sigma, const int lambda,
             const Vec &lbound, const Vec &ubound);

  Vec get_x0() const;
  Vec get_lower_bound() const;
  Vec get_upper_bound() const;
  double get_init_sigma() const;
  int get_init_lambda() const;
  int get_max_eval() const;
  int get_max_iter() const;
  double get_mu_eff() const;

  void set_termination_criteria(TerminationCriteria term_crit);
  void set_max_eval(int max_eval);
  void set_max_iter(int max_iter);
  void reset_termination_criteria();

private:
  void init();
  /*
   * General params
   */
  int m_dim;
  int m_max_eval = -1;
  int m_max_iter = -1;
  double m_target = std::numeric_limits<double>::infinity();
  double m_xtol = 1e-12;
  double m_tol_hist_fun = 1e-12;
  Vec m_x0;
  Vec m_lbound;
  Vec m_ubound;
  std::map<TerminationCriteria, bool> m_terminations;
  /*
   * CMA-ES params
   */
  int m_init_lambda = -1;
  double m_init_sigma = -1;
  int m_mu;
  double m_chi;
  double m_cs;
  double m_cc;
  double m_ccov;
  double m_cmu;
  std::vector<double> m_mu_weights;
  double m_mu_sum_weights;
  double m_mu_eff;
};

#endif
