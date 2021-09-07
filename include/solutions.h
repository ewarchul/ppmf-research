#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include "math.h"
#include "parameters.h"

class Solutions {
public:
  Solutions();
  Solutions(Parameters &params) : m_iter(0), m_evals(0) {
    std::mt19937 rng{params.get_seed()};
    std::uniform_real_distribution dist(params.get_lower_bound()[0],
                                        params.get_upper_bound()[0]);

    auto dim = static_cast<std::size_t>(params.get_dim());
    m_sigma_evopath = Vec(dim, 0);
    m_cov_evopath = Vec(dim, 0);
    m_xmean = blaze::internal::random_vec(dim, rng, dist);
    m_covariance_mat = blaze::declid(blaze::DiagonalMatrix<Matrix>(dim, 1));
    m_sigma = params.get_init_sigma();
  }

  Matrix &get_covariance_matrix() { return m_covariance_mat; }
  Population &get_population() { return m_pop; }
  Vec &get_sigma_evopath() { return m_sigma_evopath; }
  Vec &get_cov_evopath() { return m_cov_evopath; }
  Vec &get_xmean() { return m_xmean; }
  Vec &get_midpoint() { return m_midpoint; }
  Vec &get_best_sofar() { return m_best_sofar; }
  Vec &get_best_current() { return m_best_current; }
  Vec &get_eval_values() { return m_eval_values; }

  bool get_hsig() const { return m_hsig; }
  double get_sigma() const { return m_sigma; }
  double get_ptarget() const { return m_ptarget; }
  double get_dumpparam() const { return m_dumpparam; }
  unsigned int get_iter() const { return m_iter; }
  unsigned int get_evals() const { return m_evals; }

  std::string get_termination_msg() const { return m_termination_msg; }

  void set_covariance_matrix(Matrix &&mat) { m_covariance_mat = mat; }
  void set_population(Population &&pop) { m_pop = pop; }
  void set_sigma_evopath(Vec &&ps) { m_sigma_evopath = ps; }
  void set_cov_evopath(Vec &&pc) { m_cov_evopath = pc; }
  void set_hsig(bool hsig) { m_hsig = hsig; }
  void set_xmean(Vec &&xmean) { m_xmean = xmean; }
  void set_midpoint(Vec &&midpoint) { m_midpoint = midpoint; }
  void set_sigma(double sigma) { m_sigma = sigma; }
  void set_ptarget(double ptarget) { m_ptarget = ptarget; }
  void set_dumpparam(double dumpparam) { m_dumpparam = dumpparam; }
  void set_iter(unsigned int iter) { m_iter = iter; }
  void set_evals(unsigned int evals) { m_evals = evals; }
  void set_best_sofar(Vec &&best_sofar) { m_best_sofar = best_sofar; }
  void set_best_current(Vec &best_current) { m_best_current = best_current; }
  void set_termination_msg(const std::string &msg) { m_termination_msg = msg; }
  void set_eval_values(Vec eval_values) { m_eval_values = eval_values; }

  void update_log() {
    m_log_best_current.push_back(m_best_current);
    m_log_best_sofar.push_back(m_best_sofar);
    m_log_xmean.push_back(m_xmean);
    m_log_sigma.push_back(m_sigma);
  }

private:
  Matrix m_covariance_mat;
  Population m_pop;
  Vec m_eval_values;
  Vec m_xmean;
  Vec m_midpoint;
  Vec m_sigma_evopath;
  Vec m_cov_evopath;
  bool m_hsig;
  double m_sigma;
  Vec m_best_sofar;
  Vec m_best_current;

  unsigned int m_iter;
  unsigned int m_evals;

  double m_ptarget = -1;
  double m_dumpparam = -1;

  std::string m_termination_msg = "";

  std::vector<Vec> m_log_best_current;
  std::vector<Vec> m_log_best_sofar;
  std::vector<Vec> m_log_xmean;
  std::vector<double> m_log_sigma;
};

#endif
