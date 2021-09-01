#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>

#include "types.h"
#include "utils.h"

enum class TerminationCriteria { TolX };

class Parameters {
public:
  Parameters();
  Parameters(const int dim, const Vec &x0, const double sigma);
  Parameters(const Vec &x0, const double sigma);
  Parameters(const Vec &x0, const double sigma, const int lambda,
             const Vec &lbound, const Vec &ubound);

  friend struct fmt::formatter<Parameters>;

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
  Vec m_mu_weights;
  double m_mu_sum_weights;
  double m_mu_eff;
};

template <> struct fmt::formatter<Parameters> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Parameters &p, FormatContext &ctx) -> decltype(ctx.out()) {
    std::string params_format = fmt::format(
        fmt::emphasis::bold | fmt::fg(fmt::color::gold),
        "{}\nDimension := {}\nFunction evaluation budget := {}\nInitial "
        "λ:= {}\nInitial σ := {:.5}\ncs := {:.5}\n"
        "cc := {:.5}\nccov := {:.5}\ncmu := {:.5}\nmu_eff := "
        "{:.5}\n--------------\n"
        "xtol := {:.6}\ntol_hist_fun := {:.6}\ntarget := {}",
        "CMA-ES IMMUTABLE PARAMETERS:", p.m_dim, p.m_max_eval, p.m_init_lambda,
        p.m_init_sigma, p.m_cs, p.m_cc, p.m_ccov, p.m_cmu, p.m_mu_eff, p.m_xtol,
        p.m_tol_hist_fun, p.m_target);
    return format_to(ctx.out(), params_format);
  }
};

#endif
